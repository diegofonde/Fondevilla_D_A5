#include "Student.h"

Student :: Student() : Records() { //default constructor
    major = "";
    GPA = 0.0;
    advisor = 0;
}

Student :: Student(int i) : Records(i) { //overloaded constructor for id 
    major = "";
    GPA = 0.0;
    advisor = 0;
}

Student :: Student(int i, string s, string s2, string s3, double g) : Records(i, s, s2) { //overloaded constructor for every variable except advisor
    major = s3;
    GPA = g;
    advisor = 0;
}

Student :: Student(int i, string s, string s2, string s3, double g, int a) : Records(i, s, s2) { //overloaded constructor for every variable
    major = s3;
    GPA = g;
    advisor = a;
}

Student :: ~Student() { // deconstructor
    cout << "Delete Student" << endl;
}

void Student :: printInfo() const{  //print method for student
    Records :: printInfo();
    cout << "Major: " << major << endl;
    cout << "GPA: " << GPA << endl;
    if(advisor == 0) {
        cout << "Advisor: " << endl;
    }
    else {
        cout << "Advisor: " << advisor << endl;
    }
}

void Student :: setAdvisor(int i) {  //void method for setting the advisor of the student
    advisor = i;
}

int Student :: getAdvisor() { //getter method to return the advisor variable
    return advisor;
}
