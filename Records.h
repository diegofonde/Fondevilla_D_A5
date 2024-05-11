#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
using namespace std;

class Records{
    public:
        Records(); //default constructor
        Records(int i); //overloaded constrcutor for only id
        Records(int i, string s, string s2); //overloaded constructor for every variable
        ~Records(); //default constructor
        bool isEquals(Records *r);
        bool isGreater(Records *r);
        bool isLesser(Records *r);
        int getId();
        virtual void printInfo();
    protected:
        int id; //int variable for id
        string name; //string variable for name
        string level; //string variable for level

};

#endif
