#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tree.h"

#define ANSWER_MAX 1024


// Split string 'text' using delimiter 'sep', storing number into 'count'
char **split(char *text, const char *sep, unsigned int *count) {
    // Resulting array will be allocated lat
    char **res = NULL;

    // Set counter to zero
    *count = 0;

    // Start separating string
    char *p = strtok(text, sep);

    // While there is a token
    while (p) {
        // Try to reallocate space for the array
        if ((res = realloc(res, sizeof(char*) * (++*count))) == NULL)
            // Return NULL if failed
            return NULL;

        // Store the address of this token
        res[*count - 1] = p;

        // Try to get next token
        p = strtok(NULL, sep);
    }

    // Return the final array
    return res;
}


// Calculate and return size of file
// using fseek() functions
int getfsize(FILE *fp) {
    // Seek to the end of the file
    fseek(fp, 0, SEEK_END);

    // Get current (aka ending) position
    int size = ftell(fp);

    // Return to the beginning of the file
    fseek(fp, 0, SEEK_SET); 

    // Return the size of file
    return size;
}


// Read whole file
char *readall(char *filename) {
    // Create file pointer
    FILE *fp;
    
    // Open the file for reading
    if ((fp = fopen(filename, "r")) == NULL)
        return NULL;

    // Calculate size of the file
    int size = getfsize(fp);

    // Allocate enough space
    char *content = malloc(size);

    // Read whole file
    fread(content, sizeof(content), size, fp);

    // Return the content
    return content;
}


// Main function
int main(int argc, char **argv) {
    // Read file into dynamically allocated variable
    char *content = readall(argc == 1 ? "sample" : argv[1]);

    // If e.g. file does not exist, program should exit
    if (content == NULL) {
        printf("Error while reading file\n");
        return 1;
    }


    // Place to store length of file (number of lines)
    unsigned int count;

    // Split content of file by newlines
    char **lines = split(content, "\n", &count);


    // One way to create Tree
    Tree *t = Tree_create();

    // Initialize the Tree and free some space
    Tree_fromList(t, (void **) lines, count);
    free(lines);


    // Final score
    int score = 0;


    // Start main loop
    do {
        // Split the value of the current tree node
        char **qa = split(t->value, "|", &count);

        // Check if everything is OK
        if (count < 2) {
            printf("Error occured while splitting value (no answer)?");
            return 1;
        }

        // Split it further into separate variables
        char *question = qa[0], *correct = qa[1];

        // Remove leading spaces from correct answer
        while(isspace(*correct))
            correct++;

        // Remove leading spaces from question
        while(isspace(*question))
            question++;

        // Ask user the question and prompt for answer
        printf("%s\n> ", question);

        // Allocate space for answer
        char *answer = calloc(ANSWER_MAX, sizeof(int));

        // Read user input
        if (fgets(answer, ANSWER_MAX, stdin) == NULL) {
            // The fgets() function returns NULL if error/EOF occurred
            printf("EOF received, bye!\n");
            return 0;
        }

        // Remove trailing newline
        answer[strcspn(answer, "\n")] = 0;


        // Black magic to calculate score, part 1
        score <<= 1;

        // Compare user answer and the correct one
        if (strcmp(answer, correct) == 0) {

            // Go to the right node
            printf("Correct!\n");
            t = t->right;

            // Black magic to calculate score, part 2
            score |= 1;
        } else {

            // Show correct answer and go to the left node
            printf("Incorrect, the right answer was: %s\n", correct);
            t = t->left;
        }

        // Free allocated space
        free(qa);
        free(answer);
    } while (t != NULL);

    printf("Your final score is %u\n", score);
}
