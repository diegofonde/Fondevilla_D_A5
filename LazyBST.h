#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
#include "Records.h"
#include "Student.h"
#include "Faculty.h"
#include <typeinfo>
using namespace std;

template <class T>
class LazyNode {
    public:
        LazyNode(); //LazyNode default constructor
        LazyNode(T k); //LazyNode overloaded constructor
        virtual ~LazyNode(); //LazyNode deconstructor

        T key; //template variable to represent key 
        LazyNode *left; //pointer variable that stores left node
        LazyNode *right; //pointer variable that stores right node
        int leftDepth; //int variable for left depth
        int rightDepth; //int variable for right depth
};

template <class T>
LazyNode<T> :: LazyNode() { //default constructor
    key = NULL;
    left = NULL;
    right = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

template <class T>
LazyNode<T> :: LazyNode(T k) { //overloaded constructor
    key = k;
    left = NULL;
    right = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

template <class T>
LazyNode<T> :: ~LazyNode() { //deconstructor
    left = NULL;
    right = NULL;
}

template <class T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        void deconstructorHelper(LazyNode<T> *node); // Helper function for destructor

        void insert(T k); // Insert method
        bool contains(T k); // Check if tree contains given key
        T* search (T k); // Search for a key and return pointer to its data
        bool deleteNode(T k); // Delete a node with given key
        LazyNode<T>* getSuccessor(LazyNode<T> *d); // Get the successor of a node
        
        bool isEmpty(); // Check if tree is empty
        T* getMin(); // Get minimum value in the tree
        T* getMax(); // Get maximum value in the tree

        void printTree(); // Print the tree
        void recPrint(LazyNode<T> *node); // Recursive function to print tree
        void printDepths(); // Print depths of nodes
        void setID(T k, int i); // Set ID for a given key
        void setAdvisee(T k, int i); // Set advisee for a given key
        void removeAdvisee(T k, int i); // Remove advisee for a given key
        void removeAdvisor(T k); // Remove advisor for a given key
    private:
        LazyNode<T> *root; // Root node of the tree
        int total; // Total number of nodes in the tree
        bool rebuildingTree; // Flag to indicate if tree is being rebuilt
        bool needBalance(); // Check if tree needs balancing
        void fillArray(LazyNode<T>* root, T* array, int& index); // Fill array with tree elements
        void createNewTree(LazyBST<T>& tree, T* array, int start, int end); // Create new tree from array
        void balance(); // Balance the tree
        int getSize(); // Get size of the tree

};

template <class T>
LazyBST<T> :: LazyBST() {
    root = NULL;
    total = 0;
    rebuildingTree = false; // Initially set rebuildingTree flag to false
}

template <class T>
LazyBST<T> :: ~LazyBST() {
    deconstructorHelper(root); // Call helper function to delete nodes
}

template <class T>
void LazyBST<T> :: deconstructorHelper(LazyNode<T> *node) {
    if(node != nullptr) {
        deconstructorHelper(node->left); // Recursively delete left subtree
        deconstructorHelper(node->right); // Recursively delete right subtree
        delete node; // Delete current node
    }
}

template <class T>
void LazyBST<T>::recPrint(LazyNode<T> *node) {
    // Base case: if node is NULL, return
    if (node == NULL) {
        return;
    }

    // Recursively print left subtree
    recPrint(node->left);
    // Print current node's key information
    node->key.printInfo();
    cout << endl;
    // Recursively print right subtree
    recPrint(node->right);
}

template <class T>
void LazyBST<T>::printTree() {
    // Call recursive print function starting from root
    recPrint(root);
}

template <class T>
bool LazyBST<T>::isEmpty() {
    return (root == NULL); // Check if root is NULL
}

template <class T>
T* LazyBST<T>::getMin() {
    if (isEmpty()) {
        return NULL; // If tree is empty, return NULL
    }
    // Traverse leftmost nodes to find minimum key
    LazyNode<T> *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return &(current->key); // Return pointer to minimum key
}

template <class T>
T* LazyBST<T>::getMax() {
    if (isEmpty()) {
        return NULL; // If tree is empty, return NULL
    }
    // Traverse rightmost nodes to find maximum key
    LazyNode<T> *current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return &(current->key); // Return pointer to maximum key
}

template <class T>
void LazyBST<T>::insert(T k) {
    LazyNode<T> *node = new LazyNode<T>(k); // Create new node with key k

    if (isEmpty()) {
        root = node; // If tree is empty, set node as root
    } else {
        LazyNode<T> *current = root;
        LazyNode<T> *parent = NULL;

        while (true) {
            parent = current;

            if (k.isLesser(current->key)) {
                current->leftDepth = current->leftDepth + 1;
                current = current->left;

                if (current == NULL) {
                    parent->left = node; // Insert node as left child
                    break;
                }
            } else {
                current->rightDepth = current->rightDepth + 1;
                current = current->right;
                if (current == NULL) {
                    parent->right = node; // Insert node as right child
                    break;
                }
            }
        }
    }

    total += 1; // Increment total nodes count

    // Check if tree needs balancing, only if not already rebuilding
    if (rebuildingTree == false) {
        if (root != NULL && root->leftDepth >= 2 && root->rightDepth >= 2) {
            if (needBalance()) {
                cout << "need balance" << endl; // Indicate need for balancing
                balance(); // Balance the tree
            }
        }
    }
}

template <class T>
bool LazyBST<T>::contains(T k) {
    // If tree is empty, return false
    if (isEmpty()) {
        return false;
    }

    LazyNode<T> *current = root;
    // Traverse the tree until the key is found or until the end of the tree
    while (!current->key.isEquals(k)) {
        // Move to the left subtree if key is lesser
        if (k.isLesser(current->key)) {
            current = current->left;
        } else {
            // Move to the right subtree if key is greater
            current = current->right;
        }

        // If current node becomes NULL, key is not found
        if (current == NULL) {
            return false;
        }
    }

    // Key is found
    return true;
}

template <class T>
T* LazyBST<T>::search(T k) {
    // If tree is empty, return nullptr
    if (isEmpty()) {
        return nullptr;
    }

    LazyNode<T> *current = root;
    // Traverse the tree until the key is found or until the end of the tree
    while (!current->key.isEquals(k)) {
        // Move to the left subtree if key is lesser
        if (k.isLesser(current->key)) {
            current = current->left;
        } else {
            // Move to the right subtree if key is greater
            current = current->right;
        }
    } 
    // Return pointer to the key if found
    return &(current->key);
}

template <class T>
bool LazyBST<T>::deleteNode(T k) {
    // If tree is empty, return false
    if (isEmpty()) {
        return false;
    }

    LazyNode<T> *current = root;
    LazyNode<T> *parent = root;
    bool isLeft = true;
    
    // Traverse the tree until the key is found or until the end of the tree
    while (!current->key.isEquals(k)) {
        parent = current;

        // Move to the left subtree if key is lesser
        if (k.isLesser(current->key)) {
            isLeft = true;
            current->leftDepth = current->leftDepth - 1;
            current = current->left;
        } else {
            // Move to the right subtree if key is greater
            isLeft = false;
            current->rightDepth = current->rightDepth - 1;
            current = current->right;
        }

        // If current node becomes NULL, key is not found
        if (current == NULL) {
            return false;
        }
    }

    // Handle cases based on the number of children of the node to be deleted
    if (current->left == NULL && current->right == NULL) {
        // Case: Node has no children
        if (current == root) {
            root = NULL;
        } else if (isLeft) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (current->right == NULL) {
        // Case: Node has only left child
        if (current == root) {
            root = current->left;
        } else if (isLeft) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } else if (current->left == NULL) {
        // Case: Node has only right child
        if (current == root) {
            root = current->right;
        } else if (isLeft) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } else {
        // Case: Node has both left and right children
        LazyNode<T> *successor = getSuccessor(current);

        if (current == root) {
            root = successor;
        } else if (isLeft) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        // Connect the successor's left subtree to current's left subtree
        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }

    // Decrease total node count and delete current node
    total -= 1;
    delete current;
    return true;
}

template <class T>
LazyNode<T>* LazyBST<T>::getSuccessor(LazyNode<T> *d) {
    // Initialize pointers for successor and its parent
    LazyNode<T> *sp = d;
    LazyNode<T> *successor = d;
    LazyNode<T> *current = d->right;

    // Find the leftmost node in the right subtree of d
    while (current != NULL) {
        sp = successor;
        successor = current;
        current = current->left;
    }

    // Adjust pointers if successor is not the right child of d
    if (successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

template <class T>
void LazyBST<T>::balance() {
    // Set flag to indicate tree is being rebuilt
    rebuildingTree = true;

    // Create a new array to hold elements of the tree
    T* newArrayTree = new T[getSize()];
    int index = 0;
    // Fill the array with elements in sorted order
    fillArray(root, newArrayTree, index);

    // Create a new balanced tree from the sorted array
    LazyBST<T> newBST;
    createNewTree(newBST, newArrayTree, 0, getSize() - 1);

    // Update root of the current tree with root of the new balanced tree
    root = newBST.root;

    // Delete the temporary array
    delete[] newArrayTree;

    // Reset flag after tree is balanced
    rebuildingTree = false;
}

template <class T>
bool LazyBST<T>::needBalance() {
    // Check if the tree needs balancing based on depth difference between left and right subtrees
    return (root->leftDepth > 1.5 * root->rightDepth || root->rightDepth > 1.5 * root->leftDepth);
}

template <class T>
void LazyBST<T>::fillArray(LazyNode<T>* node, T* array, int& index) {
    // Recursively fill the array with elements of the tree in sorted order
    if (node != NULL) {
        fillArray(node->left, array, index);
        array[index++] = node->key;
        fillArray(node->right, array, index);
    }
}

template <class T>
void LazyBST<T>::createNewTree(LazyBST<T>& tree, T* array, int start, int end) {
    // Recursively create a new balanced tree from a sorted array
    if (start > end) {
        return;
    }

    int median = (start + end) / 2;
    T medianval = array[median];
    tree.insert(medianval);

    createNewTree(tree, array, start, median - 1);
    createNewTree(tree, array, median + 1, end);
}

template <class T>
int LazyBST<T>::getSize() {
    // Return total number of nodes in the tree
    return total;
}

template <class T>
void LazyBST<T>::printDepths() {
    // Print the depths of the root's left and right subtrees
    cout << root->leftDepth << endl;
    cout << root->rightDepth << endl;
} 

template <class T>
void LazyBST<T>::setID(T k, int i) {
    // Find the node with key k and set its advisor ID
    LazyNode<T> *current = root;
    while (!current->key.isEquals(k)) {
        if (k.isLesser(current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    } 

    current->key.setAdvisor(i);
}

template <class T>
void LazyBST<T>::setAdvisee(T k, int i) {
    // Find the node with key k and add the advisee ID to its list
    LazyNode<T> *current = root;
    while (!current->key.isEquals(k)) {
        if (k.isLesser(current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    } 

    current->key.addAdvisee(i);
}

template <class T>
void LazyBST<T>::removeAdvisee(T k, int i){
    // Find the node with key k and remove the advisee ID from its list
    LazyNode<T> *current = root;
    while (!current->key.isEquals(k)) {
        if (k.isLesser(current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    } 

    current->key.removeAdvisee(i);
}

template <class T>
void LazyBST<T>::removeAdvisor(T k) {
    // Find the node with key k and reset its advisor ID to 0
    LazyNode<T> *current = root;
    while (!current->key.isEquals(k)) {
        if (k.isLesser(current->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    } 

    current->key.setAdvisor(0);
}

#endif
