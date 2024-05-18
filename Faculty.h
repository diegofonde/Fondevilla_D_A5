#ifndef FACULTY_H
#define FACULTY_H

#include "Records.h"
#include <list>

class Faculty: public Records {
    public:
        Faculty(); //default constructor
        Faculty(int i); //overloaded method for id
        Faculty(int i, string s, string s2, string s3); //overloaded method for all variables
        ~Faculty(); //deconstructor method
        void addAdvisee(int i); //method to add advisee to the list
        void removeAdvisee(int i); //method to remove advisee from the list
        void printInfo() const override; //print method for Faculty
        list<int> getAdvisees(); //get list method
    private:
        string department; //string variable for department
        list<int> advisees; //list variable to keep track of all advisees

};

#endif
