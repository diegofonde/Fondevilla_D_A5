#include "LazyNode.h"

LazyNode :: LazyNode() {
    key = Records();
    left = NULL;
    right = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

LazyNode :: LazyNode(Records r) {
    key = r;
    left = NULL;
    right = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

LazyNode :: ~LazyNode() {
    left = NULL;
    right = NULL;
}