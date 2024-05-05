#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

template <class T>
class TreeNode{
    public: 
        TreeNode();
        TreeNode(T k);
        virtual ~TreeNode();

        T key;
        TreeNode<T> *left;
        TreeNode<T> *right;
};

template <class T>
TreeNode<T>::TreeNode() {
    left = NULL;
    right = NULL;
    key = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T k) {
    left = NULL;
    right = NULL;
    key = k;
}

template <class T>
TreeNode<T>:: ~TreeNode() {
    left = NULL;
    right = NULL;
}

template <class T>
class BST{
    public:
        BST();
        virtual ~BST();

        void insert(T value);
        bool contains(T value); //search method
        bool deleteNode(T k);
        TreeNode<T> *getSuccessor(TreeNode<T> *d);
        
        bool isEmpty();
        T* getMin();
        T* getMax();

        void printTree();
        void recPrint(TreeNode<T> *node);
    private:
        TreeNode<T> *root;
};

template <class T>
BST<T> :: BST() {
    root = NULL;
}

template <class T>
BST<T> :: ~BST() {
    //build soem character, its good for you
}

template <class T>
void BST<T> :: recPrint(TreeNode<T> *node) {

    if(node == NULL) {
        return;
    }

    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}

template <class T>
void BST<T> :: printTree() {
    recPrint(root);
}

template <class T>
bool BST<T> :: isEmpty() {
    return(root == NULL);
}

template <class T>
T* BST<T> :: getMin() {

    if(isEmpty())
        return NULL;
    
    TreeNode<T> *current = root;
    while(current->left != NULL) {
        current = current->left;
    }
    return &(current->key);
}

template <class T>
T* BST<T> :: getMax() {

    if(isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while(current->right != NULL) {
        current = current->right;
    }
    return &(current->key);
}

template <class T>
void BST<T> :: insert(T value) {
    TreeNode<T> *node = new TreeNode<T>(value);

    if(isEmpty()) {
        root = node;
    }
    else {
        //tree had more than 1 node, let's go find where it goes
        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while (true) {
            parent = current;

            if(value < current->key) {
                //we go left
                current = current->left;

                if(current == NULL) {
                    //we found the insertion point
                    parent->left = node;
                    break;
                }
            }
            else {
                //we go right
                current = current->right;
                if(current == NULL) {

                    parent->right = node;
                    break;
                }
            }
        }
    }
}

//search function O(log(n))
template <class T>
bool BST<T> :: contains(T value) {
    
    if(isEmpty()) {
        return false;
    }

    TreeNode<T> *current = root;
    while(current->key != value) {
        if(value < current->key)
            current = current ->left;
        else
            current = current->right;
        if(current == NULL)
            return false;
    }
    return true;
}

template <class T>
bool BST<T> :: deleteNode(T k) {

    if(isEmpty()) {
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    while(current->key != k) {
        parent = current;

        if(k < current->key) {
            isLeft = true;
            current = current->left;
        }
        else{
            isLeft = false;
            current = current->right;
        }

        if(current == NULL) 
            return false;
    }

    //we found the node to be deleted, let's proceed to delete

    /* node to be deleted is a leaf node*/
    if(current->left == NULL && current->right == NULL) {
        if(current == root)
            root = NULL;
        else if(isLeft)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (current->right == NULL) {
        //node has one child and its a left child
        if(current = root) {
            root = current->left;
        }
        else if (isLeft){
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
    }
    else if (current->left == NULL) {
        //node has one child and its a right child
        if(current = root) {
            root = current->right;
        }
        else if (isLeft){
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
    }
    else{
        //node to be deleted has two chidlren, at this point we begin to cry and take a 4 hour nap
        TreeNode<T> *successor = getSuccessor(current);

        if(current == root) {
            root = successor;
        }
        else if (isLeft) {
            parent->left = successor;
        }
        else {
            parent->right = successor;
        }

        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }

    //node to be deleted has 1 child
}

template <class T>
TreeNode<T>* BST<T> :: getSuccessor(TreeNode<T> *d) {

    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;
    
    while(current != NULL) {
        sp = successor;
        successor = current;
        current = current->left;
    }
    //once we get here, we found the successor
    //now we need to check if the successor is the decendant of the right child
    if(successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

#endif