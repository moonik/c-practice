#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

int main() {
    insert(24);
    insert(98);
    insert(0);
    insert(283);
    insert(3);
    insert(97);
    insert(99);
    //print(root);
    //printf("Node count: %d\n", getNodeCount(root));
    //printValues(root);
    //printf("%d", isInTree(root, 0));
    //printf("%d\n", min(root));
    //printf("%d\n", max__(root));
    //printf("%d\n", getSuccessor(root, 283));
    printf("%d", isBst(root));
    deleteValue(&root, 98);
    //print(root);
    destroy(root);
    return 0;
}