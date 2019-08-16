#define _AFXDLL
#include<string>
#include<iostream>

using namespace std;


/*Student class
Purpose: To store all information pertaining to a
student read from a .txt file. It contains
string variables m_name and m_major that store corresponding information
and int variable m_age m_test[3] and m_id.
It also contans functions that are respomsible for manipulating
its member data.
*/

class Student
{
private:
	string m_name;
	int m_age;
	string m_major;
	int m_test[3];
	int m_id;
public:
	Student(string name, int age, string major, int tests[], int id);
	Student(const Student& otherStudent);
	Student();
	bool readFromFile(ifstream& is);
	bool readFromKeyboard();
	void writeToFile(ofstream& os);
	void writeToScreen();
	string getName() const;
	int getId() const;
	int getAge() const;
	string getMajor() const;
	int getTests(int cell) const;
	void setName(const string& name);
	void setAge(const int& age);
	void setMajor(const string& major);
	void setTests(int test[], int size);
	void setId(const int& age);
};
