#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

void destroy(Node *root) {
    if (root == NULL) {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    free(root);
}


void insert(int data) {
    __insert(&root, data);
}

void __insert(Node **root, int data) {
    if (*root == NULL) {
        Node *n = malloc(sizeof(Node));
        n->data = data;
        n->left = n->right = NULL;
        *root = n;
        return;
    }

    if ((*root)->data < data) {
        __insert(&(*root)->right, data);
    } else if ((*root)->data > data) {
        __insert(&(*root)->left, data);
    } else
        (*root)->data = data;
}

void print(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d\n", root->data);
    print(root->left);
    print(root->right);
}

int getNodeCount(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + getNodeCount(root->left) + getNodeCount(root->right);
}

void printValues(Node *root) {
    if (root == NULL) {
        return;
    }
    printValues(root->left);
    printf("%d\n", root->data);
    printValues(root->right);
}

bool isInTree(Node *root, int data) {
    if (root == NULL) {
        return false;
    }
    if (root->data < data) {
        return isInTree(root->right, data);
    } else if (root->data > data) {
        return isInTree(root->left, data);
    } else
        return true;
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int min(Node *root) {
    if (root->left == NULL) {
        return root->data;
    }
    return min(root->left);
}

int max__(Node *root) {
    if (root->right == NULL) {
        return root->data;
    }
    return max__(root->right);
}

Node* findMin(Node *root) {
    if (root->left == NULL) {
        return root;
    }
    return findMin(root->left);
}

void deleteValue(Node **root, int value) {
    if ((*root) == NULL) {
        return;
    }

    if ((*root)->data < value) {
        deleteValue(&(*root)->right, value);
    } else if ((*root)->data > value) {
        deleteValue(&(*root)->left, value);
    } else {
        //case 0 children
        if ((*root)->left == NULL && (*root)->right == NULL) {
            freeNode(&(*root));
        } else if ((*root)->right == NULL) { //case 1 children (left)
            Node *tmp = *root;
            *root = tmp->left;
            freeNode(tmp);
        } else if ((*root)->left == NULL) { //case 1 children (right)
            Node *tmp = *root;
            *root = tmp->right;
            freeNode(tmp);
        } else {
            //case 2 children: find minimum value in right subtree
            Node *successor = findMin((*root)->right);
            //copy data from successor
            (*root)->data = successor->data;
            //delete successor starting from the root as right node and find the successor value
            deleteValue(&(*root)->right, successor->data);
        }
    }
}

int getSuccessor(Node *root, int data) {
    Node *current = root;
    while (current != NULL) {
        if (current->data < data) {
            current = current->right;
        } else if (current->data > data) {
            current = current->left;
        } else
            break;
    }
    if (current == NULL) {
        return -1;
    }
    if (current->right != NULL) {
        return findMin(current->right)->data;
    } else {
        Node *successor = NULL;
        Node *ancestor = root;
        while (ancestor != NULL) {
            if (ancestor->data > data) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else
                ancestor = ancestor->right;
        }
        return successor == NULL ? -1 : successor->data;
    }
}

bool isBst(Node *root) {
    return __isBst(root, INT_MIN, INT_MAX);
}

bool __isBst(Node *root, int min, int max) {
    if (root == NULL) {
        return true;
    }
    return root->data > min && root->data < max
            && __isBst(root->left, min, root->data)&&
                __isBst(root->right, root->data, max);
}

void freeNode(Node **root) {
    Node *tmp = *root;
    *root = NULL;
    free(tmp);
}