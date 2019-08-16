/*
Author: Mario Palma
Date: October 28th, 2014

Program Description: This program prompts the user to enter the name
of a .txt file that contains a list of movie titles
with other related information. The information relating
to each film listed (title, studio, year of release, etc) is
read from the file and stored in an array consisting of
Movie objects. A menu then appears and prompts the user
to enter 1 of 6 commands to manipulate the Movie array or to
end the program;
*/

#include "Assignment 3\MovieType.h"
#include "Assignment 3\SortedMovieList.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void clearScreen();
void pause();
char displayMenuAndGetSelection();
void doDisplayList(const SortedMovieList& list);
void doSearchMovieInList(const SortedMovieList& list);
void doDeleteMovieFromList(SortedMovieList& list);
void doAddMovieToList(SortedMovieList& list);
void doCountMoviesInList(const SortedMovieList& list);
void doTerminate();

void main()
{
	ifstream fin;
	string fname;
	char choice;
	bool done = false;
	SortedMovieList list;

	cout << "Hello! Enter a text file name to read from: ";
	getline(cin, fname);

	fin.open(fname);

	while (!fin)
	{
		cout << "\nError opening file!" << endl;
		cout << "Enter a text file name to read from: ";
		getline(cin, fname);
		fin.open(fname);
	}

	list.ReadAllMoviesFromFile(fin, fname);

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
			doSearchMovieInList(list);
			break;
		case '3':
			doDeleteMovieFromList(list);
			break;
		case '4':
			doAddMovieToList(list);
			break;
		case '5':
			doCountMoviesInList(list);
			break;
		case '6':
			doTerminate();
			done = true;
			break;
		default:
			cout << "Invalid selection." << endl;
			break;
		}
		pause();
	} while (!done);

	fin.close();

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
	cout << "\t'1' -- Display Movie List" << endl << endl;
	cout << "\t'2' -- Search Movie List" << endl << endl;
	cout << "\t'3' -- Delete Movie From List" << endl << endl;
	cout << "\t'4' -- Add Movie to List" << endl << endl;
	cout << "\t'5' -- Count Movies in List" << endl << endl;
	cout << "\t'6' -- Quit." << endl << endl;
	cout << "\tSelection: ";
	cin >> choice;
	cin.ignore(50, '\n');
	return toupper(choice);
}

/*void doDisplayList(const SortedMovieList& list)
Print all fields for each MovieType object in the movies[] array
Precondition: list must be valid and choice == '1'
Postcondition: none
*/
void doDisplayList(const SortedMovieList& list)
{
	list.display();
	cout << endl << endl << "Done." << endl;
}

/*void doSearchMovieInList(const SortedMovieList& list)
Search for a MovieType object in movies[] array by titile and then displaying
all of the found object's feilds
Precondition: list must be valid and choice == '2'
Postcondition: Either
The object the user was looking for is found
displays it and program terminates with return
or
Once the title goes is less than the title of an object at an index
a message displays that the movie was not found.
*/
void doSearchMovieInList(const SortedMovieList& list)
{
	string myTitle;
	MovieType itemToFind;

	cout << "Enter the title of the movie: ";
	getline(cin, myTitle);

	for (int index = 0; index < list.getLength(); index++)
	{
		list.retrieve(index, itemToFind);

		if (myTitle < itemToFind.getTitle())
		{
			cout << "\nThe movie you entered was not found.";
			return;
		}
		else if (myTitle == itemToFind.getTitle())
		{
			cout << "\nA matching movie was found:\n\n";
			cout << itemToFind;
			return;
		}
	}

	cout << "\nThe movie you entered was not found.";
}

/*void doDeleteMovieFromList(SortedMovieList& list)
Print all fields for each MovieType object in the movies[] array
Precondition: list must be valid and choice = '3'
Postcondition: The movie is found and the movie is deleted.
or
The movie is not found and nothing happanes.
*/
void doDeleteMovieFromList(SortedMovieList& list)
{
	string movieErase;
	MovieType itemToFind;
	int index = 0;

	cout << "Enter the title of the movie: ";
	getline(cin, movieErase);

	for (index; index < list.getLength(); index++)
	{
		list.retrieve(index, itemToFind);

		if (itemToFind.getTitle() == movieErase)
		{
			if (list.findAndRemove(itemToFind))
			{
				cout << "\nThe movie " << itemToFind.getTitle() << " has been deleted.\n";
				return;
			}
		}
	}

	cout << "\nThe movie you entered was not found.";
}

/*void doAddMovieToList(SortedMovieList& list)
Allows the user to enter his or her own movie in the movies[] array
Precondition: list must be valid and choice == '4'
Postcondition: The new user inputted MovieType object is added to
the movies array in alphabetical order by title.
or
The list is full and nothing can happen.
*/
void doAddMovieToList(SortedMovieList& list)
{
	string title, receipt, studio, stars;
	int year;

	if (list.getLength() == list.getMAX_LIST())
	{
		cout << endl << endl << "The list is full. You can not add any more movies\n";
		return;
	}

	cout << "Enter the movie's title: ";
	getline(cin, title);

	cout << "Enter the premire date: ";
	cin >> year;
	cin.ignore();

	cout << "Enter the adjusted gross: ";
	getline(cin, receipt);

	cout << "Enter the studio: ";
	getline(cin, studio);

	cout << "Enter the movie star names (Name1 , Name2 , etc.): ";
	getline(cin, stars);

	if (list.add(MovieType(title, year, receipt, studio, stars)))
		cout << endl << endl << "Your movie has been added." << endl;
}

/*void doCountMoviesInList(const SortedMovieList& list)
Prints how many objects are currently in the movies[] array
Precondition: list must be valid and choice == '5'
Postcondition: message is printed for the user
*/
void doCountMoviesInList(const SortedMovieList& list)
{
	cout << "There are currently " << list.getLength() << " movies in the list.\n\n";
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