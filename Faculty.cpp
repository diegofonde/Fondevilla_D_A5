#include "Faculty.h" 

Faculty :: Faculty() : Records() {
    department = "";
}

Faculty :: Faculty(int i, string s, string s2, string s3) : Records(i, s, s2) {
    department = s3;
}

Faculty :: ~Faculty() {
    //to do
}
