#define _AFXDLL
#include "Assignment4\PhoneBook.h"
#include <iostream>
#include <string>

using namespace std;

void clearScreen();
void pause();
char displayMenuAndGetSelection();
void doDisplayList(const PhoneBook& list);
void doSearchNameInPhoneBook(const PhoneBook& list);
void doDeleteNameFromPhoneBook(PhoneBook& list);
void doAddNameToPhoneBook(PhoneBook& list);
void doCountNamesInPhoneBook(const PhoneBook& list);
void doGetMaxAgeInPhoneBook(const PhoneBook& list);
void doGetPeopleWithSpecificAgeInPhoneBook(const PhoneBook& list);
void doTerminate();

void main()
{
	PhoneBook list;
	char choice;
	bool done = false;

	int *p = new int;//Used as a test to make sure memory leaks are being found by the program.
	list.Insert("B", 20, "310-456-7455");
	list.Insert("A", 46, "310-345-8000");
	list.Insert("D", 20, "320-654-7801");
	list.Insert("C", 60, "333-657-8883");
	list.Insert("Bz", 43, "310-456-7455");
	list.Insert("Az", 20, "310-345-8000");
	list.Insert("Dz", 60, "320-654-7801");
	list.Insert("Cz", 2, "333-657-8883");

	cout << "Original list: \n" << endl;
	cout << list << endl;

	//test copy ctor
	/*PhoneBook list2(list);
	cout << "List after copy ctor: \n" << endl;
	cout << list2 << endl;

	//test operator=
	PhoneBook list3;
	list3 = list;
	cout << "List after operator= : \n" << endl;
	cout << list3 << endl;*/

	cout << "End of tests. Press Enter to proceed to the menu...";
	cin.get();

	do
	{
		choice = displayMenuAndGetSelection();
		clearScreen();
		switch (choice)
		{
		case '1':
			doDisplayList(list);
			break;
		case '2':
			doSearchNameInPhoneBook(list);
			break;
		case '3':
			doDeleteNameFromPhoneBook(list);
			break;
		case '4':
			doAddNameToPhoneBook(list);
			break;
		case '5':
			doCountNamesInPhoneBook(list);
			break;
		case '6':
			doGetMaxAgeInPhoneBook(list);
			break;
		case '7':
			doGetPeopleWithSpecificAgeInPhoneBook(list);
			break;
		case '8':
			doTerminate();
			done = true;
			break;
		default:
			cout << "Invalid selection." << endl;
			break;
		}
		pause();
	} while (!done);

	return;
}

/*void clearScreen()
Clear screen
Precondition: none
Postcondition: none
*/
void clearScreen()
{
	system("cls");
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
	cout << "\t'1' -- Display Phone Book List" << endl << endl;
	cout << "\t'2' -- Search Phone Book" << endl << endl;
	cout << "\t'3' -- Delete Name From Phone Book" << endl << endl;
	cout << "\t'4' -- Add Name to Phone Book" << endl << endl;
	cout << "\t'5' -- Count Names in Phone Book" << endl << endl;
	cout << "\t'6' -- Get the Max Age from Phone Book" << endl << endl;
	cout << "\t'7' -- Find all People With a Certain Age" << endl << endl;
	cout << "\t'8' -- Quit." << endl << endl;
	cout << "\tSelection: ";
	cin >> choice;
	cin.ignore(50, '\n');
	return toupper(choice);
}

/*void doDisplayList(const PhoneBook& list)
Print all fields for each PhoneBookItem struct in the PhoneBook object
Precondition: list must be valid and choice == '1'
Postcondition: none
*/
void doDisplayList(const PhoneBook& list)
{
	cout << list << endl;
	cout << "Done." << endl;
}

/*void doSearchNameInPhoneBook(const PhoneBook& list)
Search for a PhoneBookItem struct in PhoneBook object by name and then display
all of the PhoneBookItem feilds if a match is found.
Precondition: list must be valid and choice == '2'
Postcondition: Either

The struct the user was looking for is found,
all feilds are displayed and program terminates with return
or
Once the name being searched for is less than the name of any struct in
the sorted linked list a message displays that the movie was not found.
*/
void doSearchNameInPhoneBook(const PhoneBook& list)
{
	string name = "", phone = "";
	int age = -99;

	cout << "Enter a name to look for: ";
	getline(cin, name);
	cout << endl;

	if (list.Lookup(name, age, phone))
	{
		cout << "A matching entry was found!" << endl << endl;
		cout << "Name:\t" << name << "\nAge:\t" << age << "\nPhone:\t" << phone << endl << endl;
	}
	else
		cout << "The name you entered was not found." << endl << endl;
}

/*void doDeleteNameFromPhoneBook(PhoneBook& list)
Delete a PhoneBookItem struct from the PhoneBook linked list that
matches the name the user enters.
Precondition: list must be valid and choice = '3'
Postcondition: A matching name is found in the linked list
and the corresponding struct is deleted.
or
A matching name is not found, no struct is deleted and
a message is displayed for the user to know this.
*/
void doDeleteNameFromPhoneBook(PhoneBook& list)
{
	string name = "";

	cout << "Enter a name to delete: ";
	getline(cin, name);
	cout << endl;

	if (list.Delete(name))
	{
		cout << "A matching entry was found!" << endl << endl;
		cout << name << " has been deleted.";
	}
	else
		cout << "The name you entered was not found." << endl << endl;
}

/*void doAddNameToPhoneBook(PhoneBook& list)
Allows the user to enter his or her own Phone Book entry in the PhoneBook linked list
Precondition: list must be valid and choice == '4'
Postcondition: Either
The new user inputted PhoneBookItem struct is added to
the linked list in alphabetical order by name.
or
There is already an entry in the linked list with the same
name and a message emphasizing this is displayed to the user.
*/
void doAddNameToPhoneBook(PhoneBook& list)
{
	string name = "", phone = "";
	int age = -99;

	cout << "Enter the person's name: ";
	getline(cin, name);

	cout << "Enter the person's age: ";
	cin >> age;
	cin.ignore();

	cout << "Enter the person's phone number(###-###-####): ";
	getline(cin, phone);

	if (list.Insert(name, age, phone))
		cout << endl << endl << "Your entry has been added." << endl;
	else
		cout << endl << endl << "Your was NOT added. An entry already has that name." << endl;
}

/*void doCountNamesInPhoneBook(const PhoneBook& list)
Prints how many PhoneBookItems (structs) are included in the linked list.
(Excluding the dummy node/dummy PhoneBookItem that contains no real data)
Precondition: list must be valid and choice == '5'
Postcondition: message is printed for the user
*/
void doCountNamesInPhoneBook(const PhoneBook& list)
{
	if (list.Size() == -1)
		cout << "The list is empty!";
	cout << "There are currently " << list.Size() << " names in the Phone Book.\n\n";
}

void doGetMaxAgeInPhoneBook(const PhoneBook& list)
{
	cout << "The maximum age currently in the phone book is: " << list.GetMaxAge()<< " years.";
}

void doGetPeopleWithSpecificAgeInPhoneBook(const PhoneBook& list)
{
	PhoneBook result;
	int age;

	cout << "Enter an age to find all people in the phone book with that age: ";
	cin >> age;

	result = list.GetPeopleWithGivenAge(age);

	if (result.IsEmpty())
	{
		cout << "\nNo person(s) with the entered age have been found."; 
		cin.get();
	}
	else
	{
		cout << "\nPeople matching your entered age have been found!" << endl << endl;
		cout << result;
		cout << "Done." << endl;
		cin.get();
	}
}

/*void doTerminate()
Display a message letting the user know the program has ended
Precondition: choice == '6'
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