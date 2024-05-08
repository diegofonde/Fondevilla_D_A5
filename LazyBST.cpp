#include "LazyBST.h"

LazyBST :: LazyBST() {
    root = NULL;
}

LazyBST :: ~LazyBST() {

}

void LazyBST :: recPrint(LazyNode *node) {

    if(node == NULL) {
        return;
    }

    
}

void LazyBST :: printTree() {
    recPrint(root);
}

bool LazyBST :: isEmpty() {
    return (root == NULL);
}

LazyNode* LazyBST :: getMin() {

    if(isEmpty()) {
        return NULL;
    }
    LazyNode *current = root;
    while(current->left != NULL) {
        current = current->left;
    }
    return &(current->key);
}

LazyNode* LazyBST :: getMax() {
    if(isEmpty())
        return NULL;

    LazyNode *current = root;
    while(current->right != NULL) {
        current = current->right;
    }
    return &(current->key);
}