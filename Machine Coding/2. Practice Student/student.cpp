#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
private:
	int id;
	string name;
	double marks;
public:
	Student(int id, string name, double marks) {
		this->id = id;
		this->name = name;
		this->marks = marks;
	}

	int getId() {
		return id;
	}

	void setName(string name) {
		this->name = name;
	}

	string getName() {
		return name;
	}

	void setMarks(double marks) {
		this->marks = marks;
	}

	double getMarks() {
		return marks;
	}
};

class Manager {
private:
	vector<Student*> allStudents;
public:
	~Manager() {
		for (auto student : allStudents) {
			delete student;
		}
	}

	void addStudent(int id, string name, double marks) {
		allStudents.push_back(new Student(id, name, marks));
	}

	void updateStudent(int id, string name, double marks) {
		for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {
			if ((*it)->getId() == id) {
				(*it)->setName(name);
				(*it)->setMarks(marks);
				cout << "Student Id: " << id << " updated successfully!\n";
				return;
			}
		}
		cout << "Student Id: " << id << " not found\n";
	}

	void deleteStudent(int id) {
		for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {
			if ((*it)->getId() == id) {
				delete *it;  // Delete the dynamically allocated Student object
				allStudents.erase(it);  // Erase the pointer from the vector
				cout << "Student Id: " << id << " deleted successfully!\n";
				return;
			}
		}
		cout << "Student Id: " << id << " not found\n";
	}

	void display() const {
		for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {
			cout << "Id: " << (*it)->getId() << ", Name: " << (*it)->getName()
					<< ", Marks: " << (*it)->getMarks() << "\n";
		}
	}
};

int main() {
	Manager m1;

	m1.addStudent(1, "Naveen1", 100);
	m1.addStudent(2, "Naveen2", 10);
	m1.addStudent(3, "Naveen3", 10);

	cout << "Initial list of students:\n";
	m1.display();

	m1.updateStudent(2, "Hari Krishna", 20);
	m1.deleteStudent(3);

	cout << "\nUpdated list of students:\n";
	m1.display();

	return 0;
}

/*

 Initial list of students:
 Id: 1, Name: Naveen1, Marks: 100
 Id: 2, Name: Naveen2, Marks: 10
 Id: 3, Name: Naveen3, Marks: 10
 Student Id: 2 updated successfully!
 Student Id: 3 deleted successfully!

 Updated list of students:
 Id: 1, Name: Naveen1, Marks: 100
 Id: 2, Name: Hari Krishna, Marks: 20

 */
