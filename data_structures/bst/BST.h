#ifndef PROJECT_BST_H
#define PROJECT_BST_H

#define max(a, b) a > b ? a : b

#include <stdbool.h>

typedef struct Node Node;

struct Node {
   int data;
   Node *left;
   Node *right;
};

Node *root;

void destroy(Node *root);

/*
 * inserts value into tree
 */
void insert(int data);
void __insert(Node **root, int data);

/*
 * pre-order traversal (dfs pre-order)
 */
void print(Node *root);

/*
 * returns number of nodes
 */
int getNodeCount(Node *root);

/*
 * prints values in ascending order (dfs in-order traversal)
 */
void printValues(Node *root);

/*
 * checks whether value is in the tree
 */
bool isInTree(Node *root, int data);

/*
 * returns height of tree
 */
int height(Node *root);

/*
 * return minimum value
 */
int min(Node *root);

/*
 * returns maximum value
 */
int max__(Node *root);

/*
 * returns true if tree is binary search tree
 */
bool isBst(Node *root);

bool __isBst(Node *root, int min, int max);

/*
 * deletes node with value
 */
void deleteValue(Node **root, int value);

/*
 * returns next-highest value in tree after given value, -1 if none
 */
int getSuccessor(Node *root, int data);

Node* findMin(Node *root);

void freeNode(Node **root);

#endif //PROJECT_BST_H
