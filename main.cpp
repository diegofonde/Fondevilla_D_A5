#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std; 
int main(int argc, char* argv[]) {

    BST<int> *b = new BST<int>(); 

    b->insert(5);
    b->insert(1);
    b->insert(10);

    cout << b->getMax() << endl;
    cout << b->getMin() << endl;

    return 0;
}