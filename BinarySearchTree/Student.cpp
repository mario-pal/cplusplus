#define _AFXDLL
#include "Student.h"
#include <string>
#include <fstream>

using namespace std;

const string StopName = "***";

/* Student::Student()
Purpose: Default constructor for Student object.
Precondition: none.
Postcondition: All member feilds of the student object are initialized.
*/
Student::Student()
{
	m_name = "";
	m_age = -99;
	m_major = "";
	m_test[3];
	m_id = -99;
}

/* Student::Student(const Student& otherStudent)
Purpose: Copy constructor for Student object.
Precondition: none.
Postcondition: All member feilds of the student object are initialized, copying the otherStudent member feilds.
*/
Student::Student(const Student& otherStudent)
{
	m_name = otherStudent.m_name;
	m_age = otherStudent.m_age;
	m_major = otherStudent.m_major;
	for (int cell = 0; cell < 3; cell++)
		m_test[cell] = otherStudent.m_test[cell];
	m_id = otherStudent.m_id;
}

/* bool Student::readFromFile(ifstream& is)
Purpose: Initialize a Student object's member data from data read from a .txt file.
Precondition: Tree object must be initialized and ifstream object must be initialized.
Postcondition: All member feilds of the student object are initialized, copying the input from a chosen .txt file.
*/
bool Student::readFromFile(ifstream& is)
{
	getline(is, m_name);

	if (m_name == StopName)
	{
		return false;
	}

	getline(is, m_major);

	is >> m_age;

	for (int cell = 0; cell < 3; cell++)
	{
		int test;
		is >> test;
		m_test[cell] = test;
	}

	is >> m_id;
	is.ignore();
	return true;
}

/* bool Student::readFromKeyboard()
Purpose: Initialize a Student object's member data from data read the information the user inputs.
Precondition: Tree object must be initialized.
Postcondition: All member feilds of the student object are initialized, copying the user input from the console.
*/
bool Student::readFromKeyboard()
{
	getline(cin, m_name);

	if (m_name == StopName)
	{
		return false;
	}

	getline(cin, m_major);

	cin >> m_age;

	for (int cell = 0; cell < 3; cell++)
	{
		int test;
		cin >> test;
		m_test[cell] = test;
	}

	cin >> m_id;
	cin.ignore();
	return true;
}

/* void Student::writeToFile(ofstream& os)
Purpose: Write data in Student member feilds to a file.
Precondition: Tree object must be initialized.
Postcondition: All member feilds of the student object are written to a designated file.
*/
void Student::writeToFile(ofstream& os)
{
	os << m_name << endl;
	os << m_major << endl;
	os << m_age << endl;

	for (int cell = 0; cell < 3; cell++)
	{
		os << m_test[cell];
		os << " ";
	}

	os << endl;
	os << m_id << endl;
}

/* string Student::getName() const
Purpose: To access private m_name variable.
Precondition: none.
Postcondition: m_name value is returned.
*/
string Student::getName() const
{
	return m_name;
}

/* int Student::getId() const
Purpose: To access private m_id variable.
Precondition: none.
Postcondition: m_id value is returned.
*/
int Student::getId() const
{
	return m_id;
}

/* int Student::getAge() const
Purpose: To access private m_age variable.
Precondition: none.
Postcondition: m_age value is returned.
*/
int Student::getAge() const
{
	return m_age;
}

/* string Student::getMajor() const
Purpose: To access private m_major variable.
Precondition: none.
Postcondition: m_major value is returned.
*/
string Student::getMajor() const
{
	return m_major;
}

/* int Student::getTests(int cell) const
Purpose: To access private m_test variable.
Precondition: none.
Postcondition: The value in m_test[cell] is returned.
*/
int Student::getTests(int cell) const
{
	return m_test[cell];
}

/* void Student::setName(const string& name)
Purpose: To access private m_name variable.
Precondition: none.
Postcondition: m_name value is returned.
*/
void Student::setName(const string& name)
{
	m_name = name;
}

/* void Student::setAge(const int& age)
Purpose: To access private m_age variable.
Precondition: none.
Postcondition: m_age value is returned.
*/
void Student::setAge(const int& age)
{
	m_age = age;
}

/* void Student::setMajor(const string& major)
Purpose: To access private m_major variable.
Precondition: none.
Postcondition: m_major value is returned.
*/
void Student::setMajor(const string& major)
{
	m_major = major;
}

/* void Student::setTests(int test[], int size)
Purpose: Set all cells in m_test[] to the values of the test being passed.
Precondition: none.
Postcondition: All m_test[] cells are initialized.
*/
void Student::setTests(int test[], int size)
{
	for (int cell = 0; cell < size; cell++)
	{
		m_test[cell] = test[cell];
	}
}

/*void Student::setId(const int& id)
Purpose: Set m_id to the id being passed.
Precondition: none.
Postcondition: m-id now contains the value of id.
*/
void Student::setId(const int& id)
{
	m_id = id;
}