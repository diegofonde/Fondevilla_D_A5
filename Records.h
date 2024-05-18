#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
using namespace std;

class Records{
    public:
        Records(); //default constructor
        Records(int i); //overloaded constrcutor for only id
        Records(int i, string s, string s2); //overloaded constructor for every variable
        virtual ~Records(); //default constructor
        bool isEquals(Records r); //is equals method
        bool isGreater(Records r); //is greater method
        bool isLesser(Records r); //is lesser method
        int getId(); //get id method
        virtual void printInfo() const; //print method for records class
    protected:
        int id; //int variable for id
        string name; //string variable for name
        string level; //string variable for level

};

#endif
