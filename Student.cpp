#include "Student.h"

Student :: Student() : Records() {
    major = "";
    GPA = 0.0;
    advisor = 0;
}

Student :: Student(int i, string s, string s2, string s3, double g, int a) : Records(int i, string s, string s2) {
    major = s3;
    GPA = double;
    advisor = a;
}

Student :: ~Student() {
    //to do
}
