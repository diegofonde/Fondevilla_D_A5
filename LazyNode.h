#ifndef LAZYNODE_H
#define LAZYNODE_H

#include <iostream>
#include "Records.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;

template <class T>
class LazyNode {
    public:
        LazyNode();
        LazyNode(T k);
        virtual ~LazyNode();

        T key;
        LazyNode *left;
        LazyNode *right;
        int leftDepth;
        int rightDepth;
};

template <class T>
LazyNode<T> :: LazyNode() {
    key = NULL;
    left = NULL;
    right = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

template <class T>
LazyNode<T> :: LazyNode(T k) {
    key = k;
    left = NULL;
    right = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

template <class T>
LazyNode<T> :: ~LazyNode() {
    left = NULL;
    right = NULL;
}

#endif