#pragma once

// Binary Tree structure and type
typedef struct Tree {
    void *value;
    struct Tree *left;
    struct Tree *right;
} Tree;


// Function to initialize Tree
void Tree_init(Tree *t);


// Function to create Tree using malloc()
Tree *Tree_create(void);

// Commented because this is internal function
// not intended for running outside the library
// void Tree_build(Tree *t);


// Public function to create a Tree from a list.
// Internally it just sets some values and calls
// the other recursive internal function
void Tree_fromList(Tree *t, void **list, int length);
