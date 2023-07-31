#include "header.h"

bool quit = false;

int main(void) {
	list <student> database; //this linked list will contain a student record object in each node


	cout << "Welcome to the student grade database." << endl;
	cout << "Developed by: ENGM2283 Project Group 9" << endl;
	cout << "Andrew Michels, Bora Atakli, Colby Connell, Jackson Lewis, and Shishir Ghosh" << endl << endl;
	while (!quit) {
		char choice;
		// print main menu
		cout << endl;
		cout << "C : clear database" << endl;
		cout << "S : sort students by average final grade" << endl;
		cout << "A : add a student" << endl;
		cout << "P : pick a student in the database" << endl;
		cout << "V : view database statistics" << endl;
		cout << "Q : quit" << endl;
		cin >> choice;

		if (choice == 'C') { //clears linked list database
			database.clearList();

		}
		else if (choice == 'S') { //sorts students in database by final grade (average) and prints results
			list<student> orderedDatabase;
			char sortChoice;
			cout << "press * to automatically load database with some students for testing: ";
			cin >> sortChoice;
			if (sortChoice == '*') {
				

				//automatically add some students with average grades to the database to test sorting more easily
				student student1 = student(1, 67);
				database.store(student1);
				student student2 = student(2, 56);
				database.store(student2);
				student student3 = student(3, 100);
				database.store(student3);
				student student4 = student(4, 79);
				database.store(student4);
				student student5 = student(5, 98);
				database.store(student5);


				database.write(cout);
			}

			student max =  database.findmax();
			orderedDatabase = database;

			node<student>* a = orderedDatabase.getstart();

			//cout << "start: " << a;

			cout << "Sorting by final grade... " << endl;
			
			// 
			//database.MergeSort(&a);
			//database.printList(database.sort(a), cout);
			
			//cout << "element at a: " << database.getdata(a);

			//sorted = database.sorting(database.getstart());
			// 
			orderedDatabase.printList(orderedDatabase.sorting(a), cout);

			database.store(max);
			

			//cout << "start: " << a;
			//
			//database.write(cout);

		}
		else if (choice == 'A') { //adds new student (node to linked list)
			student newStudent;
			int newID;
			cout << "Enter new student information: " << endl;

			cout << "ID: ";
			cin >> newID;
			newStudent.setID(newID);

			database.store(newStudent);

			//check if student added successfully:
			database.write(cout);
		}
		else if (choice == 'P') { //searches for student by id and enters submenu
			int searchID;
			student FoundStudent;
			bool found = false;
			cout << "Enter id: ";
			cin >> searchID;

			FoundStudent = database.searchForStudent(searchID);

			if (FoundStudent.getID() != NULL) {
				bool stayinmenu2 = true;
				while (stayinmenu2) {
					char choice2;
					//print info for found student and submenu
					cout << "Student with ID " << searchID << " is:" << endl;
					cout << FoundStudent;
					cout << endl;
					cout << "V : View student's grades" << endl;
					cout << "A : Add new course" << endl;
					cout << "G : Add grade to course" << endl;
					cout << "S : Type specific functions" << endl;
					cout << "D : Delete student record" << endl;
					cout << "Q : Go back to main menu" << endl;

					cin >> choice2;

					if (choice2 == 'V') { //prints student's grades and other info
						FoundStudent.write(cout);
					}
					else if (choice2 == 'A') { //adds new course to selected student
						//add new course
						FoundStudent.addCourse();

						//replace old record with modified version
						database.pop_search(searchID);
						database.store(FoundStudent);
					}
					else if (choice2 == 'G') { //adds grade to selected course in selected student; if course does not exist, prints error message
						char type;
						cout << "What category of course? ('t' for test-based, 'p' for project based): ";
						cin >> type;
						string courseName;
						//char choice3;
						cout << "Enter course name: ";
						cin >> courseName;
						float newGrade;
						cout << "Enter new grade: ";
						cin >> newGrade;
						bool found;
						if (type == 'p') {
							projectBasedCourse FoundCourse = FoundStudent.findProjectCourse(courseName, found);
							if (found) {
								FoundCourse.addGrade(newGrade);
								//cout << "final grade: " << FoundCourse.getFgrade() << endl;
								FoundStudent.updatePcourse(courseName, FoundCourse);
								FoundStudent.avgStudentGrade();
							}
							else {
								cout << "Unable to add grade, course not found" << endl;
							}

						}
						else if (type == 't') {
							testBasedCourse FoundCourse = FoundStudent.findTestCourse(courseName, found);
							if (found) {
								FoundCourse.addGrade(newGrade);
								FoundStudent.updateTcourse(courseName, FoundCourse);
								FoundStudent.avgStudentGrade();
							}
							else {
								cout << "Unable to add grade, course not found" << endl;
							}
						}
						//replace old record with modified version
						database.pop_search(searchID);
						database.store(FoundStudent);

					}
					else if (choice2 == 'S') { //adds additional info to selected course in selected student; if course does not exist, prints error message
						//enter date or number tests
						char type;
						cout << "What category of course? ('t' for test-based, 'p' for project-based): ";
						cin >> type;

						string courseName;
						cout << "Enter course name: ";
						cin >> courseName;

						bool found;

						if (type == 't') {
							int numTests;
							cout << "Enter number of tests written: ";
							cin >> numTests;
							testBasedCourse FoundCourse = FoundStudent.findTestCourse(courseName, found);
							if (found) {
								FoundCourse.setNumTests(numTests);
								FoundStudent.updateTcourse(courseName, FoundCourse);
							}
							else {
								cout << "Data not added, course not found" << endl;
							}
						}
						else if (type == 'p') {
							string dueDate;
							cout << "Enter project due date: ";
							cin >> dueDate;
							projectBasedCourse FoundCourse = FoundStudent.findProjectCourse(courseName, found);
							if (found) {
								FoundCourse.setDueDate(dueDate);
								FoundStudent.updatePcourse(courseName, FoundCourse);
							}
							else {
								cout << "Data not added, course not found" << endl;
							}
						}
						//replace old record with modified version
						database.pop_search(searchID);
						database.store(FoundStudent);
					}
					else if (choice2 == 'D') { //deletes selected student record from linked list
						database.pop_search(searchID);
						stayinmenu2 = false;
					}
					else if (choice2 == 'Q') { //returns to main menu, saves any changes made to student record
						stayinmenu2 = false;
						//replace old record with modified version
						database.pop_search(searchID);
						database.store(FoundStudent);
					}	
				}
			}
		}
		else if (choice == 'V') { //print linked list count
			int numberOfStudents = database.size();
			cout << "There are " << numberOfStudents << " students in the database." << endl;
		}
		else if (choice == 'Q') { //quits program
			quit = true;

		}

	}

	return 0;

}
