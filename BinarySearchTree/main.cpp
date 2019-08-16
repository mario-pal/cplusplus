/*
Author: Mario Palma
Date: December 4th, 2014

Program Description: Read data from a .txt file and stores
it in memory. A menu system allows the
user to manipulate the data as necessary.
The manipulated data in memory can the be save to a file.
*/

#define _AFXDLL
#include <iostream>
#include <fstream>
#include <string>
//#include "Assignment 5\Tree.h"
#include "Tree.h"
//#include "Tree.cpp"
//#include "Student.h"
//#include "Student.cpp"
using namespace std;

void clearScreen();
void pause();
char displayMenuAndGetSelection();
void doReadFromFile(Tree& myTree);
void doWriteToFile(const Tree& myTree);
void doSearchForStudent(const Tree& myTree);
void doAddStudent(Tree& myTree);
void doRemoveStudent(Tree& myTree);
void doDisplayData(const Tree& myTree);
void doTerminate();

int main()
{
	Tree myTree;
	char choice;
	bool done = false;

	do
	{
		choice = displayMenuAndGetSelection();
		clearScreen();
		switch (choice)
		{
		case '1':
			doReadFromFile(myTree);
			break;
		case '2':
			doWriteToFile(myTree);
			break;
		case '3':
			doSearchForStudent(myTree);
			break;
		case '4':
			doAddStudent(myTree);
			break;
		case '5':
			doRemoveStudent(myTree);
			break;
		case '6':
			doDisplayData(myTree);
			break;
		case '7':
			doTerminate();
			done = true;
			break;
		default:
			cout << "Invalid selection." << endl;
			break;
		}
		pause();
	} while (!done);
	return 0;
}

/*void clearScreen()
Clear screen
Precondition: none
Postcondition: none
*/
void clearScreen()
{
//	system("cls");
}

/*void pause()
Let the user see confirmation of input
Precondition: none
Postcondition: none
*/
void pause()
{
	cout << endl << endl << "Press 'ENTER' to continue...." << endl;
	cin.ignore(50, '\n');
}

/*char displayMenuAndGetSelection()
Print the menu prompt
Precondition: none
Postcondition: none
*/
char displayMenuAndGetSelection()
{
	char choice;
	clearScreen();
	cout << "Welcome to the main menu!" << endl;
	cout << "Select an action by entering its corresponding integer.";
	cout << endl << endl << endl;
	cout << "\t'1' -- Read Data From File" << endl << endl;
	cout << "\t'2' -- Write Data To File" << endl << endl;
	cout << "\t'3' -- Search For A Student" << endl << endl;
	cout << "\t'4' -- Add New Student" << endl << endl;
	cout << "\t'5' -- Remove Student" << endl << endl;
	cout << "\t'6' -- Display Data" << endl << endl;
	cout << "\t'7' -- Quit." << endl << endl;
	cout << "\tSelection: ";
	cin >> choice;
	cin.ignore(50, '\n');
	return toupper(choice);
}

/*void doReadFromFile(Tree& myTree)
Read all data from .txt file and call readFromFile and Insert function.
Precondition: myTree must be valid and choice == '1'
Postcondition: none
*/
void doReadFromFile(Tree& myTree)
{
	Student myStudent;
	ifstream fin;
	string fname;

	cout << "Enter a text file name to read from: ";
	getline(cin, fname);

	fin.open("f.txt");

	while (!fin)
	{
		cout << "\nError opening file!" << endl;
		cout << "Enter a text file name to read from: ";
		getline(cin, fname);
		fin.open("f.txt");
	}

	while (myStudent.readFromFile(fin))
	{
		if (!myTree.Insert(myStudent))
			break;
	}

	fin.close();

	cout << endl << "Done reading file.";
}

/*void doWriteToFile(const Tree& myTree)
Write all data to a .txt file and call writeToFile function.
Precondition: myTree must be valid and choice == '2'
Postcondition: Output file now has all data in BST written to it.
*/
void doWriteToFile(const Tree& myTree)
{
	ofstream fout;

	cout << "Writing to file filecopy.txt... ";

	fout.open("filecopy.txt");

	while (!fout)
	{
		cout << "\nError opening file filecopy.txt!" << endl;
		cin.get();
		return;
	}

	myTree.Write(myTree.getRoot(), fout);

	cout << "Successfully written to filecopy.txt";

	fout.close();
}

/*void doSearchForStudent(const Tree& myTree)
Search for student in BST by calling Lookup function and print to screen all its feilds.
Precondition: myTree must be valid, and sorted and choice == '3'
Postcondition: none.
*/
void doSearchForStudent(const Tree& myTree)
{
	int id;
	Student myStudent;

	cout << "Enter a student's ID to look for: ";
	cin >> id;
	cin.ignore();

	myStudent.setId(id);

	if (myTree.Lookup(myStudent))
	{
		cout << endl << myStudent.getName() << " was found!" << endl << endl;
		myTree.writeToScreen(myStudent);
	}
	else
	{
		cout << endl << "Student " << id << " was NOT found!";
	}
	//cin.ignore();
	//cin.get();
}

/*void doAddStudent(Tree& myTree)
Add any number of new students to the BST by calling readFromKeyboard and Insert function.
Precondition: myTree must be valid, sorted and choice == '4'.
Postcondition: BST contains all new Student object entries in sorted order.
*/
void doAddStudent(Tree& myTree)
{
	Student myStudent;
	string name, major;

	cout << "Enter the student's information below (End info with '***'): ";
	cout << endl;

	while (myStudent.readFromKeyboard())
	{
		if (myTree.Insert(myStudent))
			cout << endl << myStudent.getName() << " was successfully added." << endl << endl;
		else
			cout << endl << endl << myStudent.getName() << " could NOT be added! There already exists a student with the same ID number." << endl << endl;
	}

}

/*void doRemoveStudent(Tree& myTree)
Remove student from the BST based on user entered student id by calling the Delete function.
Precondition: myTree must be valid, sorted and choice == '5'.
Postcondition: BST removes new Student object entry.
*/
void doRemoveStudent(Tree& myTree)
{
	int id;

	cout << "Enter the ID number of the student you want to remove: ";
	cin >> id;
	cin.ignore();

	if (myTree.Delete(id))
		cout << endl << "Student " << id << " was successfully deleted.";
	else
		cout << endl << "Student " << id << " could NOT be deleted!";
	//cin.ignore();
	//cin.get();
}

/*void doDisplayData(const Tree& myTree)
Print all member feilds in each node in the Binary Search Tree (BST).
Precondition: myTree must be valid, sorted and choice == '6'.
Postcondition: none.
*/
void doDisplayData(const Tree& myTree)
{
	cout << myTree;
	cout << endl << "Done";
}

/*void doTerminate()
Display a message letting the user know the program has ended
Precondition: choice == '7'
Postcondition: none
*/
void doTerminate()
{
	cout << endl << endl << endl << endl << endl;
	cout << "                 *******************************************" << endl;
	cout << "                 *   P R O G R A M  T E R M I N A T E D    *" << endl;
	cout << "                 *                                         *" << endl;
	cout << "                 *               Goodbye!                  *" << endl;
	cout << "                 *******************************************" << endl;
	cout << endl << endl << endl << endl << endl;
}
