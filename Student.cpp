#include "Student.h"

Student :: Student() : Records() {
    major = "";
    GPA = 0.0;
    advisor = 0;
}

Student :: Student(int i, string s, string s2, string s3, double g, int a) : Records(i, s, s2) {
    major = s3;
    GPA = g;
    advisor = a;
}

Student :: ~Student() {
    //to do
}

void Student :: printInfo() {
    Records :: printInfo();
    cout << "Major: " << major << endl;
    cout << "GPA: " << GPA << endl;
    cout << "Advisor: " << advisor << endl;
}
