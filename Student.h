#ifndef STUDENT_H
#define STUDENT_H

#include "Records.h"

class Student: public Records {
    public:
        Student();
        Student(int i, string s, string s2, string s3, double g, int a);
        ~Student();
        void printInfo() override;
    private:
        string major;
        double GPA;
        int advisor;

};

#endif
