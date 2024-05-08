#include "Records.h"

Records::Records() {
    id = 0;
    name = "";
    level = "";
}

Records::Records(int i) {
    id = i;
    name = "";
    level = "";
}

Records::Records(int i, string s, string s2) {
    id = i;
    name = s;
    level = s2;
}

Records::~Records() {
    //to do
}

bool Records::isEquals(Records *r) {
    return(id == r->getId());
}

bool Records::isGreater(Records *r) {
    return(id > r->getId());
}

bool Records::isLesser(Records *r) {
    return(id < r->getId());
}

int Records::getId() {
    return id;
}
