#include "Records.h"

Records::Records() { //default constructor
    id = 0;
    name = "";
    level = "";
}

Records::Records(int i) { //overloaded constructor 
    id = i;
    name = "";
    level = "";
}

Records::Records(int i, string s, string s2) { //second overloaded constructor
    id = i;
    name = s;
    level = s2;
}

Records::~Records() {
    cout << "Delete Records" << endl;
}

bool Records::isEquals(Records r) { //is equals method which compares id value
    return(id == r.getId());
}

bool Records::isGreater(Records r) { //is greater method which compares id value 
    return(id > r.getId());
}

bool Records::isLesser(Records r) { //is lesser method which compared id value
    return(id < r.getId());
}

int Records::getId() { //get id method
    return id;
}

void Records :: printInfo() const { //print method for records
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl; 
}
