#include "LazyNode.h"

LazyNode :: LazyNode() {
    id = 0;
    key = NULL;
    left = NULL;
    right = NULL;
}

LazyNode :: LazyNode(Records *r) {
    id = r->getId();
    key = r;
    left = NULL;
    right = NULL;
}

LazyNode :: ~LazyNode() {
    left = NULL;
    right = NULL;
}