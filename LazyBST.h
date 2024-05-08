#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
#include "LazyNode.h"
using namespace std;

class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();

        void insert(T value);
        bool contains(T value); //search method
        bool deleteNode(T k);
        TreeNode<T> *getSuccessor(TreeNode<T> *d);
        
        bool isEmpty();
        T* getMin();
        T* getMax();

        void printTree();
        void recPrint(LazyNode *node);
    private:
        LazyNode *root;
        int total;
        int leftSubTreeDepth;
        int rightSubTreeDepth;
};

#endif
