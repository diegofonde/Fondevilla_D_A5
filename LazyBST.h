#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
#include "LazyNode.h"
using namespace std;

class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();

        void insert(Records *r);
        void search(int id); //search method
        // bool deleteNode(T k);
        // TreeNode<T> *getSuccessor(TreeNode<T> *d);
        
        bool isEmpty();
        Records* getMin();
        Records* getMax();

        void printTree();
        void recPrint(LazyNode *node);
    private:
        LazyNode *root;
        int total;
        int leftSubTreeDepth;
        int rightSubTreeDepth;
};

#endif
