#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class node {
	template <typename U> friend class list;    // list can access node's private members
private:
	T data;         // this is the data stored in a node
	static T initial;
	node* next;      // pointer to the next node in the list
public:
	node(T&);      // data = x, next = NULL      
};

template <typename T>
class list {
private:
	node<T>* start;     // pointer to node at the start of the list
	int count;        // number of nodes in the list

public:
	list(void);											// constructor of an empty list
	void store(T& item);								// push the item at the start
	int size(void) const;								// return count
	bool empty(void) const;								// check for an empty list
	void write(ostream& out) const;						// send the stored data to out
	T searchForStudent(int searchID);					// return the item containing searchID
	void clearList(void);								// remove all nodes in list
	void pop_search(int deleteID);						// remove the item containing deleteID
	T getdata(node<T>* ptr);
	// 
	node<T>* merge(node<T>* list1, node<T>* list2);
	node<T>* sorting(node<T>* start);

	T findmax(void);


//	node<T>* merge2(node<T>* firstNode, node<T>* secondNode);
//	node<T>* middle(node<T>* head);
//	node<T>* sort(node<T>* head);

	void printList(node<T>* node, ostream& out) const;
	node<T>* getstart(void);
};



// class COURSE

class course {
protected:
	float assignmentGrade;
	float examGrade;
	float finalGrade;
	string coursename;

public:
	course(float Agrade = 0, float Egrade = 0, float Fgrade = 0, string cname = "");
	string getName(void);
	float getFgrade(void);
	void write(ostream& out) const;
};


// class TESTBASEDCOURSE inherits from class COURSE

class testBasedCourse : public course {
protected:
	int numberOfTestsWritten;
	float testGrade;

public:
	testBasedCourse(float Agrade = 0, float Egrade = 0, float Fgrade = 0, string cname = "", float Tgrade = 0, int numTests = 0);
	float calculateGrade(float Agrade, float Egrade, float Tgrade);
	void addGrade(float newGrade);
	void setNumTests(int numTests);
	virtual void write(ostream& out) const;
};

// class PROJECTBASEDCOURSE inherits from class COURSE

class projectBasedCourse : public course {
protected:
	string projectDueDate;
	float projectGrade;

public:
	projectBasedCourse(float Agrade = 0, float Egrade = 0, float Fgrade = 0, string cname = "", float Pgrade = 0, string dueDate = "\0");
	float calculateGrade(float Agrade, float Egrade, float Pgrade);
	void addGrade(float newGrade);
	void setDueDate(string dueDate);
	virtual void write(ostream& out) const;
};



class student {
protected:
	int id;
	float studentAvg;
	vector <testBasedCourse> Tcourses;
	vector <projectBasedCourse> Pcourses;

public:
	student(int ID = 0, float average = 0);
	void setID(int ID);
	int getID(void);
	float getStudentAvg(void);

	void avgStudentGrade(void);
	void addCourse(void);
	testBasedCourse findTestCourse(string courseName, bool& found);
	projectBasedCourse findProjectCourse(string courseName, bool& found);
	void updatePcourse(string name, projectBasedCourse temp);
	void updateTcourse(string name, testBasedCourse temp);
	virtual void write(ostream& out) const;

	friend ostream& operator<<(ostream& out, const student& stdt);
	friend bool operator>=(const student& sA, const student& sB);
	friend bool operator<=(const student& sA, const student& sB);
};




//include template methods in header

template <typename T>
node<T>::node(T& x) {      // data = x, next = NULL 
	data = x;
	next = NULL;
}

template <typename T>
list<T>::list(void) {       // constructor of an empty list
	start = NULL;
	count = 0;
}

template <typename T>
void list<T>::store(T& item) { // push the item at the start
	node<T>* ptr = new node<T>(item);
	ptr->next = start;
	start = ptr;
	count++;
}

template <typename T>
T list<T>::getdata(node<T>* ptr) {
	return ptr->data;
}

template <typename T>
node<T>* list<T>::merge(node<T>* list1, node<T>* list2) {
	node<T>* comblist;
	
    if (list1 == NULL) {
        return list2;
    } else if (list2 == NULL) {
        return list1;
    } else if (list1->data >= list2->data) {
        comblist = list1;
        comblist->next = merge(list1->next, list2);
    } else {
        comblist = list2;
        comblist->next = merge(list1, list2->next);
    }
    return comblist;
}


template <typename T>
node<T>* list<T>::sorting(node<T>* start) {
	 if (start == NULL || start->next == NULL) {
        return start;
    }

    node<T>* ptr_lead = start, *ptr_lag = start, *center = start;

    if (start == NULL || start->next == NULL) {
        center = start;
    }
    else {
        while (ptr_lead->next != NULL)
        {
            ptr_lead = ptr_lead->next;

            if (ptr_lead->next == NULL)
                break;

            ptr_lead = ptr_lead->next;
            ptr_lag = ptr_lag->next;
        }
        center = ptr_lag;
    }
   
    node<T>* list1 = start;
    node<T>* list2 = center->next;

    center->next = NULL;
    list1 = sorting(list1);
    list2 = sorting(list2);
    node<T>* comblist = merge(list1, list2);

    return comblist;
}

template <typename T>
T list<T>::findmax(void) {
	T max = T(0, 0);
	for (node<T>* ptr = start; ptr != NULL; ptr = ptr->next) {
		if (ptr->data >= max) {
			max = ptr->data;
		}
	}
	count--;
	return max;
}

/*
template<typename T>
node<T>* list<T>::merge2(node<T>* firstNode, node<T>* secondNode)
{
	node<T>* merged = new node<T>;
	node<T>* temp = new node<T>;

	// Merged is equal to temp so in the 
	// end we have the top Node.
	merged = temp;

	// while either firstNode or secondNode 
	// becomes NULL
	while (firstNode != NULL &&
		secondNode != NULL)
	{
		if (firstNode->data >=
			secondNode->data)
		{
			temp->next = firstNode;
			firstNode = firstNode->next;
		}

		else
		{
			temp->next = secondNode;
			secondNode = secondNode->next;
		}
		temp = temp->next;
	}

	// Any remaining Node in firstNode or 
	// secondNode gets inserted in the temp 
	// List
	while (firstNode != NULL)
	{
		temp->next = firstNode;
		firstNode = firstNode->next;
		temp = temp->next;
	}

	while (secondNode != NULL)
	{
		temp->next = secondNode;
		secondNode = secondNode->next;
		temp = temp->next;
	}

	// Return the head of the sorted list
	return merged->next;
}

// Function to calculate the middle 
// Element
template<typename T>
node<T>* list<T>::middle(node<T>* head)
{
	node<T>* slow = head;
	node<T>* fast = head->next;

	while (slow->next != NULL &&
		(fast != NULL && fast->next != NULL))
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

template<typename T>
node<T>* list<T>::sort(node<T>* head)
{
	if (head->next == NULL)
	{
		return head;
	}

	node<T>* mid = new node<T>;
	node<T>* head2 = new node<T>;
	mid = middle(head);
	head2 = mid->next;
	mid->next = NULL;

	// Recursive call to sort() hence diving 
	// our problem, and then merging the solution
	node<T>* finalhead = merge(sort(head),
		sort(head2));
	return finalhead;
}*/


template <typename T>
void list<T>::printList(node<T>* a, ostream& out) const {
	node<T>* temp = a;

	while (temp != NULL) {
		out << temp->data << endl;
		temp = temp->next;
	}
}


template <typename T>
int list<T>::size(void) const {
	return count;
}

template <typename T>
bool list<T>::empty(void) const {
	return (count == 0);
}

template <typename T>
void list<T>::write(ostream& out) const {
	out << endl << "Database contains the following students:" << endl;
	for (node<T>* ptr = start; ptr != NULL; ptr = ptr->next) {
		out << ptr->data << endl;
	}
	out << endl;
}

template <typename T>
T list<T>::searchForStudent(int searchID) {
	//node<T>* nothing = NULL;
	if (empty()) {
		//isfound = false;
		cout << "database empty" << endl;
		return T();
	}
	else {
		node<T>* ptr = start;

		T currentStudent = ptr->data;
	
		while (1) {
			currentStudent = ptr->data;
			int intCurrentID = currentStudent.getID();

			if (intCurrentID == searchID) {
				return currentStudent;	
			}

			if (ptr->next == NULL) {	
				break;
			}
			ptr = ptr->next;
		}

		cout << "student not in database" << endl;
		return T(); //if not found, return empty student record with message
	}

}


template <typename T>
void list<T>::clearList(void) {
	node<T>* ptr;
	while (start!=NULL) {
		ptr = start;
		start = start->next;
		delete ptr;
		count--;
	}	
}


template<typename T>
node<T>* list<T>::getstart(void) {
	return start;
}

template <typename T>
void list<T>::pop_search(int deleteID) {
	node<T>* ptr = start;
	node<T>* ptr_lag = start;
	if (count == 1) {
		start = ptr->next;
		
	}
	else {
		T currentStudent = start->data;
		int intCurrentID = currentStudent.getID();

		//cout << "start->data: ";
		//(ptr->data).write(cout);

		while (intCurrentID != deleteID) {
			currentStudent = ptr->data;
			intCurrentID = currentStudent.getID();

			if (intCurrentID != deleteID) {
				ptr_lag = ptr;
				ptr = ptr->next;
			}
		}

		//cout << "deleting: ";
		//(ptr->data).write(cout);
		//cout << "p_lag: ";
		//(ptr_lag->data).write(cout);
		if (ptr==ptr_lag) {
			start = ptr->next;
		}
		else {
			ptr_lag->next = ptr->next;
		}
		
	}
	delete ptr;
	count--;
}



