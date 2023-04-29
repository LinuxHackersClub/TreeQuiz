#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Binary Tree structure and type
typedef struct Tree {
    void *value;
    struct Tree *left;
    struct Tree *right;
} Tree;


// Function to initialize Tree
void Tree_init(Tree *t) {
    t->value = NULL;
    t->right = NULL;
    t->left = NULL;
}


// Function to create Tree using malloc()
Tree *Tree_create(void) {
    Tree *t = malloc(sizeof(Tree));
    Tree_init(t);
    return t;
}


// Static here means that all variables are
// internal to this file/object
static int _length;
static void ** _list;
static void Tree_build(Tree *t, int depth) {
    t->value = *(_list++);
    if (2 << depth == _length + 1) {
        return;
    }

    t->right = Tree_create();
    t->left = Tree_create();

    Tree_build(t->right, depth + 1);
    Tree_build(t->left,  depth + 1);
}


// Public function to create a Tree from a list.
// Internally it just sets some values and calls
// the other recursive internal function
bool Tree_fromList(Tree *t, void **list, int length) {
    if (length & (length + 1))
        return false;

    _list = list;
    _length = length;
    Tree_build(t, 0);

    return true;
}
