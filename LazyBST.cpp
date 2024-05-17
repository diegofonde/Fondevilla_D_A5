#include "LazyBST.h"
#include <typeinfo>

LazyBST :: LazyBST() {
    root = NULL;
    total = 0;
    rebuildingTree = false;
}

LazyBST :: ~LazyBST() {

}

void LazyBST :: recPrint(LazyNode *node) {

    if(node == NULL) {
        return;
    }

    recPrint(node->left);
    cout << node->key.getId();
    recPrint(node->right);
}

void LazyBST :: printTree() {
    recPrint(root);
}

bool LazyBST :: isEmpty() {
    return (root == NULL);
}

Records* LazyBST :: getMin() {

    if(isEmpty()) {
        return NULL;
    }
    LazyNode *current = root;
    while(current->left != NULL) {
        current = current->left;
    }
    return &(current->key);
}

Records* LazyBST :: getMax() {
    if(isEmpty())
        return NULL;

    LazyNode *current = root;
    while(current->right != NULL) {
        current = current->right;
    }
    return &(current->key);
}

void LazyBST :: insert(Records r) {
    LazyNode *node = new LazyNode(r);
    

    if(isEmpty()) {
        root = node;
    }
    else {
        LazyNode *current = root;
        LazyNode *parent = NULL;

        while(true) {
            parent = current;

            if(r.isLesser(current->key)) {
                current->leftDepth = current->leftDepth + 1;
                current = current->left;

                if(current == NULL) {
                    parent->left = node;
                    break;
                }
            }
            else {
                current->rightDepth = current->rightDepth +1;
                current = current->right;
                if(current == NULL) {

                    parent->right = node;
                    break;
                }
            }
        }
    }

    total += 1;

    if (rebuildingTree == false)
    {
        if (root != NULL && root->leftDepth >= 2 && root->rightDepth >= 2) {
            if (needBalance()) {
                cout << "need balance" << endl;
                balance();
            }
        }
    }
    
}

bool LazyBST :: contains(Records r) {
    if(isEmpty()) {
        return false;
    }

    LazyNode *current = root;
    while(!current->key.isEquals(r)) {
        if(r.isLesser(current->key)) {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if(current == NULL) {
            return false;
        }
    }

    return true;
}

Records* LazyBST :: search(Records r) {
    LazyNode *current = root;
    while(!current->key.isEquals(r)) {
        if(r.isLesser(current->key)) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    } 
    return &(current->key);
}

Student* LazyBST :: studentSearch(Records r) {
    Records *searching = search(r);
    const std::type_info& objectType = typeid(*searching);
    if(objectType == typeid(Student)) {
        cout << "This is a student" << endl;
    }
    else {
        cout << "This is a Record" << endl;
    }
    Student *s = dynamic_cast<Student*>(searching);
    return s;
}

Faculty* LazyBST :: facultySearch(Records r) {
    Records *searching = search(r);
    Faculty *f = dynamic_cast<Faculty*>(searching);
    return f;
}

void LazyBST :: printInfo(Records r) {
    search(r)->printInfo();
}

bool LazyBST :: deleteNode(Records r) {

    if(isEmpty()) {
        return false;
    }

    LazyNode *current = root;
    LazyNode *parent = root;
    bool isLeft = true;
    
    while(!current->key.isEquals(r)) {
        parent = current;

        if(r.isLesser(current->key)) {
            isLeft = true;
            current->leftDepth = current->leftDepth - 1;
            current = current->left;
        }
        else {
            isLeft = false;
            current->rightDepth = current->rightDepth - 1;
            current = current->right;
        }

        if(current == NULL) {
            return false;
        }
    }

    if(current->left == NULL && current->right == NULL) {
        if(current == root) {
            root = NULL;
        }
        else if (isLeft) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
    }
    else if (current->right == NULL) {
        if(current = root) {
            root = current->left;
        }
        else if (isLeft) {
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
    }
    else if (current->left == NULL) {
        if(current = root) {
            root = current->right;
        }
        else if (isLeft) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
    }
    else {
        LazyNode *successor = getSuccessor(current);

        if(current == root) {
            root = successor;
        }
        else if (isLeft) {
            parent->left = successor;
        }
        else {
            parent->right = successor;
        }

        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }

    total -= 1;
    delete current;
    return true;
}

LazyNode* LazyBST :: getSuccessor(LazyNode *d) {

    LazyNode *sp = d;
    LazyNode *successor = d;
    LazyNode *current = d->right;

     while(current != NULL) {
        sp = successor;
        successor = current;
        current = current->left;
    }
    if(successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

void LazyBST :: balance() {
    rebuildingTree = true;
    Records* newArrayTree = new Records[getSize()];
    int index = 0;
    fillArray(root, newArrayTree, index);

    LazyBST newBST;
    createNewTree(newBST, newArrayTree, 0, getSize() - 1);

    root = newBST.root;

    delete[] newArrayTree;

    rebuildingTree = false;

}

bool LazyBST :: needBalance() {
    return(root->leftDepth > 1.5 * root->rightDepth || root->rightDepth > 1.5 * root->leftDepth);
}

void LazyBST :: fillArray(LazyNode* node, Records* array, int& index) {
    if (node != NULL) {
        fillArray(node->left, array, index);
        array[index++] = node->key;
        fillArray(node->right, array, index);
    }
}

void LazyBST :: createNewTree(LazyBST& tree, Records* array, int start, int end) {
    if(start > end) {
        return;
    }

    int median = (start + end)/2;
    Records medianval = array[median];
    tree.insert(medianval);

    createNewTree(tree, array, start, median - 1);
    createNewTree(tree, array, median + 1, end);
}

int LazyBST :: getSize() {
    return total;
}

void LazyBST :: printDepths() {
    cout << root->leftDepth << endl;
    cout << root->rightDepth << endl;
} 