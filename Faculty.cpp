#include "Faculty.h" 

Faculty :: Faculty() : Records() { //default constructor
    department = "";
}


Faculty :: Faculty(int i) : Records(i) { //overloaded constructor for id
    department = "";
}

Faculty :: Faculty(int i, string s, string s2, string s3) : Records(i, s, s2) { //overloaded constructor for all variavkes
    department = s3;
}

Faculty :: ~Faculty() { //deconstructor
    cout << "Delete Faculty" << endl;
}

void Faculty :: addAdvisee(int i) {
    advisees.push_back(i);
}

void Faculty :: removeAdvisee(int i) {
    advisees.remove(i);
}

list<int> Faculty :: getAdvisees() {
    return advisees;
}

void Faculty :: printInfo() const {
    Records :: printInfo();
    cout << "Department: " << department << endl;
    cout << "Advisees: ";
    for(const auto& id : advisees) {
        cout << id << " ";
    }
    cout << endl;
}
