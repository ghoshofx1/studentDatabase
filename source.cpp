#include "header.h"

///////////// implementation of class student //////////////

student::student(int ID, float average) : Tcourses(0), Pcourses(0) {
    id = ID;
    studentAvg = average;
}

float student::getStudentAvg(void) {
    return studentAvg;
}

void student::setID(int ID) { id = ID; }

int student::getID(void) { return id; }

void student::avgStudentGrade(void) {
    float totalTcourses = 0, totalPcourses = 0;
    for (int i = 0; i < Tcourses.size(); i++) {
        totalTcourses = totalTcourses + Tcourses[i].getFgrade(); // get total grade for tcourses
    }
    for (int i = 0; i < Pcourses.size(); i++) {
        totalPcourses = totalPcourses + Pcourses[i].getFgrade(); // get total grade for pcourses
    }

    studentAvg = (totalTcourses + totalPcourses) / (Tcourses.size() + Pcourses.size());
}

void student::addCourse(void) {

    //Pcourses.push_back(projectBasedCourse(0, 0, 0, "TEST"));

    char type;
    cout << "Project based course or Test Based course? (Enter 'p' or 't'): ";
    cin >> type;

    string name;
    cout << "Enter new course name: ";
    cin >> name;

    if (type == 'p') {

        projectBasedCourse newCourse(0, 0, 0, name);
        Pcourses.push_back(newCourse);
        //p_push_back(newCourse);
        //newCourse.write(cout);
        //Pcourses[0].write(cout);
        //Pcourses[1].write(cout);



    }
    else if (type == 't') {
        testBasedCourse newCourse(0, 0, 0, name);
        Tcourses.push_back(newCourse);
    }

    cout << "course " << name << " added to student #" << id << endl;
}

void student::updateTcourse(string name, testBasedCourse temp) {

    for (int i = 0; i < Tcourses.size(); i++) {
        if (Tcourses[i].getName() == name) {
            Tcourses.erase(Tcourses.begin() + i);
        }
    }
    Tcourses.push_back(temp);
}

void student::updatePcourse(string name, projectBasedCourse temp) {

    for (int i = 0; i < Pcourses.size(); i++) {
        if (Pcourses[i].getName() == name) {
            Pcourses.erase(Pcourses.begin() + i);
        }
    }
    Pcourses.push_back(temp);
}

void student::write(ostream& out) const {
    out << "Printing record for student #" << id << endl << endl;
    out << "Project-based courses: " << endl;
    //out << "size: " << Pcourses.size() << endl;
    for (int i = 0; i < Pcourses.size(); i++) {
        Pcourses[i].write(out);
    }
    out << "Test-based courses: " << endl;
    for (int i = 0; i < Tcourses.size(); i++) {
        Tcourses[i].write(out);
    }
}

testBasedCourse student::findTestCourse(string courseName, bool& found) {
    found = false;
    if (Tcourses.empty()) {
        return testBasedCourse();
    }
    else {
        int i = 0;
        for (i = 0; i < Tcourses.size(); i++) {
            if (Tcourses[i].getName() == courseName) {
                found = true;
            }
            
        }
        return Tcourses[i];
    }
}

projectBasedCourse student::findProjectCourse(string courseName, bool& found) {
    found = false;
    if (Pcourses.empty()) {
        return projectBasedCourse();
    }
    else {
        int i = 0;
        for (i = 0; i < Pcourses.size(); i++) {
            if (Pcourses[i].getName() == courseName) {
                found = true;
            }
        }
        return Pcourses[i];
    }
}

ostream& operator<<(ostream& out, const student& stdt) { // friend overloaded operator to print student
    out << "ID: " << stdt.id << endl;
    out << "Average final grade (GPA): " << stdt.studentAvg << endl;
    out << "Number of test-based courses: " << stdt.Tcourses.size() << endl;
    out << "Number of project-based courses: " << stdt.Pcourses.size() << endl;

    return out;
}

bool operator>=(const student& sA, const student& sB) { // friend overloaded operator to compare students
    bool sA_big = false;
    if (sA.studentAvg >= sB.studentAvg) {
        sA_big = true;
    }
    return sA_big;
}

bool operator<=(const student& sA, const student& sB) { // friend overloaded operator to compare students
    bool sA_small = false;
    if (sA.studentAvg <= sB.studentAvg) {
        sA_small = true;
    }
    return sA_small;
}


///////////// implementation of class course /////////////////
course::course(float Agrade, float Egrade, float Fgrade, string cname) {
    assignmentGrade = Agrade;
    examGrade = Egrade;
    finalGrade = Fgrade;
    coursename = cname;
}

float course::getFgrade(void) { return finalGrade; }

void course::write(ostream& out) const {
    out << coursename << " final grade: " << finalGrade << endl;
}

string course::getName(void) { return coursename; }

///////////// implementaion of class testBasedCourse /////////////////

testBasedCourse::testBasedCourse(float Agrade, float Egrade, float Fgrade,
    string cname, float Tgrade, int numTests)
    : course(Agrade, Egrade, Fgrade, cname) {
    testGrade = Tgrade;
    numberOfTestsWritten = numTests;
}

void testBasedCourse::addGrade(float newGrade) {

    char type;
    cout << "Select type of new grade";
    cout << " ('a' for assignments, 'e' for exam, 't' for tests, or 'p' for "
        "project): ";
    cin >> type;
    if (type == 'a') {
        assignmentGrade = newGrade;
    }
    else if (type == 'e') {
        examGrade = newGrade;
    }
    else if (type == 't') {
        testGrade = newGrade;
    }

    finalGrade = calculateGrade(assignmentGrade, examGrade, testGrade);

}

void testBasedCourse::write(ostream& out) const {
    out << coursename << " final grade: " << finalGrade;
    out << ", number of tests written: " << numberOfTestsWritten << endl;
}



float testBasedCourse::calculateGrade(float Agrade, float Egrade, float Tgrade) {
    float grade = 0.1 * Agrade + 0.4 * Egrade + 0.5 * Tgrade;
    return grade;
}

void testBasedCourse::setNumTests(int numTests) {
    numberOfTestsWritten = numTests;
}

///////////// implementaion of class testBasedCourse /////////////////

projectBasedCourse::projectBasedCourse(float Agrade, float Egrade, float Fgrade,
    string cname, float Pgrade,
    string dueDate)
    : course(Agrade, Egrade, Fgrade, cname) {
    projectGrade = Pgrade;
    projectDueDate = dueDate;
}

void projectBasedCourse::addGrade(float newGrade) {

    char type;
    cout << "Select type of new grade";
    cout << " ('a' for assignments, 'e' for exam, 't' for tests, or 'p' for "
        "project): ";
    cin >> type;
    if (type == 'a') {
        assignmentGrade = newGrade;
    }
    else if (type == 'e') {
        examGrade = newGrade;
    }
    else if (type == 'p') {
        projectGrade = newGrade;
    }

    finalGrade = calculateGrade(assignmentGrade, examGrade, projectGrade);
    //cout << "final grade = " << finalGrade << endl;

}

void projectBasedCourse::write(ostream& out) const {
    out << coursename << " final grade: " << finalGrade;
    out << ", project due date: " << projectDueDate << endl;
}

float projectBasedCourse::calculateGrade(float Agrade, float Egrade, float Pgrade) {
    float grade = 0.1 * Agrade + 0.3 * Egrade + 0.6 * Pgrade;
    return grade;
}

void projectBasedCourse::setDueDate(string dueDate) {
    projectDueDate = dueDate;
}




