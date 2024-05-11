#ifndef LAZYNODE_H
#define LAZYNODE_H

#include <iostream>
#include "Records.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;

class LazyNode {
    public:
        LazyNode();
        LazyNode(Records *r);
        virtual ~LazyNode();

        int id;
        Records *key;
        LazyNode *left;
        LazyNode *right;
};

#endif