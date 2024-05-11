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

Records* LazyBST :: getMin() {

    if(isEmpty()) {
        return NULL;
    }
    LazyNode *current = root;
    while(current->left != NULL) {
        current = current->left;
    }
    return &(current->key);
}

Records* LazyBST :: getMax() {
    if(isEmpty())
        return NULL;

    LazyNode *current = root;
    while(current->right != NULL) {
        current = current->right;
    }
    return &(current->key);
}

void LazyBST :: insert(Records *r) {
    LazyNode *node = new LazyNode(r);
    

    if(isEmpty()) {
        root = node;
    }
    else {
        LazyNode *current = root;
        LazyNode *parent = NULL;

        while(true) {
            parent = current;

            if(r->getId() < current->id) {
                current = current->left;

                if(current == NULL) {
                    parent->left = node;
                    break;
                }
            }
            else {
                current = current->right;
                if(current == NULL) {

                    parent->right = node;
                    break;
                }
            }
        }
    }
}

Records* LazyBST :: search(int id) {
    if(isEmpty()) {
        return NULL;
    }

    LazyNode *current = root;
    while(current->id != id) {
        if(id < current->id) {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if(current == NULL) {
            return NULL;
        }
    }

    return current->key;
}