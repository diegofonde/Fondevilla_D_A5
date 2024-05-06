#ifndef FACULTY_H
#define FACULTY_H

#include "Records.h"

class Faculty: public Records {
    public:
        Faculty();
        Faculty(int i, string s, string s2, string s3);
    private:
        string department;

};

#endif
