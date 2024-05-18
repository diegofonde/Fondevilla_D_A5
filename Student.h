#ifndef STUDENT_H
#define STUDENT_H

#include "Records.h"

class Student: public Records {
    public:
        Student(); //default constructor
        Student(int i); //overloaded constructor for id
        Student(int i, string s, string s2, string s3, double g); //overloaded constructor for every variable except advisor
        Student(int i, string s, string s2, string s3, double g, int a); //overloaded constructor for every variable
        void setAdvisor(int i); //void method for setting the advisor of the student
        ~Student(); // deconstructor
        int getAdvisor(); //getter method to return the advisor variable
        void printInfo() const override; //print method for student
    private:
        string major; //string variable for major 
        double GPA; //double variable for GPA
        int advisor; //int variable for advisor

};

#endif
