#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "LazyBST.h"
#include "Records.h"
#include "Student.h"
#include "Faculty.h"

using namespace std; 

int main(int argc, char* argv[]) {

    // Create instances of LazyBST for students and faculty
    LazyBST<Student> *s = new LazyBST<Student>();
    LazyBST<Faculty> *f = new LazyBST<Faculty>();

     // Create sample student and faculty objects and insert them into respective trees
    Student diego(100, "Diego Fondevilla", "Sophomore", "Data Science", 4.0, 1);
    s->insert(diego);
    Faculty rene(1, "Rene German", "Professor", "Fowler");
    rene.addAdvisee(100);
    f->insert(rene);

    // Initialize variables for user input and unique IDs for students and faculty
    int choice = 0;
    int facultyid = 2;
    int studentid = 101;

    //prints out options for users
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the student id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Add a new student" << endl;
    cout << "6. Delete a student given the id" << endl;
    cout << "7. Add a new faculty member" << endl;
    cout << "8. Delete a faculty member given the id" << endl;
    cout << "9. Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "10. Remove an advisee from a faculty member given the ids" << endl;
    cout << "11. Exit" << endl;

    //while loop keeps going until input is 11
    while (choice != 11) {
        cout << "Input your choice: " << endl;
        cin >> choice;

        //choice one prints the student tree
        if(choice == 1) {
            s->printTree();
        } 
        else if(choice == 2) { //choice two prints the faculty tree
            f->printTree();
        }
        else if(choice == 3) { //choice 3 makes user input student id, checks if it valid and it exists then searches student
            cout << "Please input the students id: " << endl;
            int studentSearchID;
            cin >> studentSearchID;
            if(studentSearchID < 100) {
                cout << "This id is not a student id." << endl;
            }
            else {
                Student studentSearch(studentSearchID);
                if(s->contains(studentSearch)) {
                    s->search(studentSearch)->printInfo();
                }
                else {
                    cout << "Student does not exist." << endl;
                }
            }

        }
        else if(choice == 4) { //choice 4 makes user input faculty id, checks if it valid and it exists then searches faculty
            cout << "Please input the faculty id: " << endl;
            int facultySearchID;
            cin >> facultySearchID;
            if(facultySearchID >= 100) {
                cout << "This id is not a faculty id." << endl;
            }
            else {
                Faculty facultySearch(facultySearchID);
                if(f->contains(facultySearch)) {
                    f->search(facultySearch)->printInfo();  
                }
                else {
                    cout << "Faculty does not exist." << endl;
                }
            }
        }
        else if (choice == 5) { //choice 5 allows user to input details about the student and create a student object which will be added to the student tree
            cout << "The Students id is: " << studentid << endl;

            string name;
            cout << "Please enter the Students Name: " << endl;
            cin.ignore();
            getline(cin, name);

            string level;
            cout << "Please enter the Students level: " << endl;
            getline(cin, level);

            string major;
            cout << "Please enter the Students Major: " << endl;
            getline(cin, major);

            double GPA;
            cout << "Please enter the Students GPA" << endl;
            cin >> GPA;
            Student studentAdd(studentid, name, level, major, GPA);
            studentid++;
            s->insert(studentAdd);
        }
        else if (choice == 6) { //choice 6 lets the user input a student id, check if it valids and it exists then delete the student from the tree
            int studentDeleteID;
            cout << "Input the id of the student you want to delete: " << endl;
            cin >> studentDeleteID;
            if(studentDeleteID < 100) {
                cout << "This is not a student id" << endl;
            }
            else {
                Student studentDelete(studentDeleteID);
                if(s->contains(studentDelete)) {
                    int del = s->search(studentDelete)->getAdvisor();
                    s->deleteNode(studentDelete);
                    Faculty advisor(del);
                    f->removeAdvisee(advisor, studentDeleteID);
                    
                }
                else {
                    cout << "Student does not exist." << endl;
                }
            }
        }
        else if (choice == 7) { //choice 7 allows user to input details about the faculty and create a faculty object which will be added to the faculty tree
            cout << "The Faculty id is: " << facultyid << endl;

            string name2;
            cout << "Please enter the Facultys Name: " << endl;
            cin.ignore();
            getline(cin, name2);

            string level2;
            cout << "Please enter the Facultys level: " << endl;
            getline(cin, level2);

            string department;
            cout << "Please enter the Facultys Department: " << endl;
            getline(cin, department);
            
            Faculty facultyAdd(facultyid, name2, level2, department);
            facultyid++;
            f->insert(facultyAdd);
        }
        else if (choice == 8) { //choice 8 lets the user input a faculty id, check if it valids and it exists then delete the faculty from the tree
            int facultyDeleteID;
            cout << "Input the id of the faculty you want to delete: " << endl;
            cin >> facultyDeleteID;
            if(facultyDeleteID >= 100) {
                cout << "This is not a student id" << endl;
            }
            else {
                Faculty facultyDelete(facultyDeleteID);
                if(f->contains(facultyDeleteID)) {
                    for(const auto& id : f->search(facultyDeleteID)->getAdvisees()) {
                        Student temp(id);
                        s->removeAdvisor(temp);
                    }
                    f->deleteNode(facultyDeleteID);
                }
                else {
                    cout << "Faculty does not exist." << endl;
                }
            }
        }
        else if (choice == 9) { //choice 9 lets the user input a student id then checks if its valid and it exists. After that makes user input a faculty id and checks if its valid and exist. After that it assigns that faculty id as the students advisor
            int studentChange;
            int facultyChange;
            cout << "Input the id of the Student you want to assign a faculty: " << endl;
            cin >> studentChange;
            Student stu(studentChange);
            if(!s->contains(stu)) {
                cout << "Student does not exist." << endl;
            }
            else {
                cout << "Input the id of the faculty you want to assign the student to." << endl;
                cin >> facultyChange;
                Faculty fac(facultyChange);
                if(!f->contains(fac)) {
                    cout << "Faculty does not exist." << endl;
                }
                else {
                    int facultynum = f->search(fac)->getId();
                    int studentnum = s->search(stu)->getId();
                    s->setID(stu, facultynum);
                    f->setAdvisee(fac, studentnum);
                }
            }

        }
        else if (choice == 10) { //choice 10 lets the user input a student id then checks if its valid and it exists. After that makes user input a faculty id and checks if its valid and exist. After that it removes the student id from the list of advisees in the faculty object
            int studentChange;
            int facultyChange;
            cout << "Input the id advisee: " << endl;
            cin >> studentChange;
            Student stu(studentChange);
            if(!s->contains(stu)) {
                cout << "Student does not exist." << endl;
            }
            else {
                cout << "Input the id of the advisor." << endl;
                cin >> facultyChange;
                Faculty fac(facultyChange);
                if(!f->contains(fac)) {
                    cout << "Faculty does not exist." << endl;
                }
                else {
                    int studentnum = s->search(stu)->getId();
                    f->removeAdvisee(fac, studentnum);

                }
            }
        }
        else if (choice == 11) { //choice 11 exits the program
            cout << "You are now exiting the program." << endl;
        }
        else {
            cout << "Invalid input, please try again." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    delete s;
    delete f;



    return 0;
}