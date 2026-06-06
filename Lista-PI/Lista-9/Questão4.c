#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void check_null(void *p) {
    if (p == NULL) {
        printf("Erro Aloc\n");
        exit(1);
    }
}

typedef struct TreeNode {
    struct TreeNode *leftPtr;
    int data;
    struct TreeNode *rightPtr;
} TreeNode;

typedef TreeNode *TreeNodePtr;

void insertNode(TreeNodePtr *treePtr, int value) {
    if (*treePtr == NULL) {
        *treePtr = malloc(sizeof(TreeNode));
        check_null(*treePtr);
        (*treePtr)->data = value;
        (*treePtr)->leftPtr = NULL;
        (*treePtr)->rightPtr = NULL;
    }
    else {
        if (value < (*treePtr)->data)
            insertNode(&((*treePtr)->leftPtr), value);
        else if (value > (*treePtr)->data)
            insertNode(&((*treePtr)->rightPtr), value);
    }
}

void preOrder(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        printf(" %d", treePtr->data);
        preOrder(treePtr->leftPtr);
        preOrder(treePtr->rightPtr);
    }
}

void inOrder(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        inOrder(treePtr->leftPtr);
        printf(" %d", treePtr->data);
        inOrder(treePtr->rightPtr);
    }
}

void postOrder(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        postOrder(treePtr->leftPtr);
        postOrder(treePtr->rightPtr);
        printf(" %d", treePtr->data);
    }
}

int countNodes(TreeNodePtr treePtr) {
    if (treePtr == NULL) {return 0;}
    else { return 1 + countNodes(treePtr->leftPtr) + countNodes(treePtr->rightPtr); }
}

int countBranches(TreeNodePtr treePtr){
    if (treePtr == NULL) {return 0;}
    else if (treePtr->leftPtr == NULL && treePtr->rightPtr == NULL){return 1;}
    else { return countBranches(treePtr->leftPtr) + countBranches (treePtr->rightPtr); }
}

int countHeight(TreeNodePtr treePtr){
    if (treePtr == NULL){return -1;}
    else { return 1 + MAX(countHeight(treePtr->leftPtr), countHeight(treePtr->rightPtr)); }
}

int lowestNumber(TreeNodePtr treePtr) {
    if (treePtr->leftPtr == NULL){return treePtr->data;}
    else {return lowestNumber(treePtr->leftPtr);}
}

int highestNumber (TreeNodePtr treePtr){
    if (treePtr->rightPtr == NULL){return treePtr->data;}
    else {return highestNumber(treePtr->rightPtr);}
}

int main(void) {
    TreeNodePtr rootPtr = NULL;
    int inteiro;

    while (scanf(" %d", &inteiro) == 1 && inteiro != -1)
        insertNode(&rootPtr, inteiro);

    if (rootPtr == NULL) {
        printf("ARVORE VAZIA\n");
    }
    else {
        printf("PREORDEM:");
        preOrder(rootPtr);
        printf("\n");

        printf("EMORDEM:");
        inOrder(rootPtr);
        printf("\n");

        printf("POSORDEM:");
        postOrder(rootPtr);
        printf("\n");

        printf("TOTAL DE NOS: %d\n", countNodes(rootPtr));
        printf("FOLHAS: %d\n", countBranches(rootPtr));
        printf("ALTURA: %d\n", countHeight(rootPtr));
        printf("MENOR: %d\n", lowestNumber(rootPtr));
        printf("MAIOR: %d\n", highestNumber(rootPtr));
    }
}