#include "MovieType.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

const string StopName = "***";

/* MovieType::MovieType(string title, int year, string receipt, string studio, string stars)
	Purpose: Constructor that initializes strings to "" and ints to 0
*/
MovieType::MovieType(string title, int year, string receipt, string studio, string stars)
:m_title(title), m_year(year), m_receipt(receipt), m_studio(studio), m_stars(stars)
{}

/* MovieType::MovieType()
	Purpose: No argument constructor that initializes strings to "" and ints to 0
*/
MovieType::MovieType()
: m_title(""), m_year(0), m_receipt(""), m_studio(""), m_stars("")
{}


/* void MovieType::Initialize(string title, int year, string receipt, string studio, string stars)
	Purpose: Places data in the MovieType feilds.
	Precondition: none
	Postcondition: All fields have a value.
*/
void MovieType::Initialize(string title, int year, string receipt, string studio, string stars)
{
	m_title = title;
	m_year = year;
	m_receipt = receipt;
	m_studio = studio;
	m_stars = stars;
}

/* ostream& operator<<(ostream& os, const MovieType& m)
	Purpose: Print the values of the member data for a MovieType variable.
	Precondition: m must be valid
	Postcondition: return os
*/
ostream& operator<<(ostream& os, const MovieType& m)
{
	m.display(os);
	return os;
}


/* void MovieType::display(ostream& os) const
Purpose: Print the values of the member data for a MovieType variable with appropriate formatting.
Precondition: m (representing MovieType variable)
Postcondition: os stores what is to be printed
*/
void MovieType::display(ostream& os) const
{
	string tempReceipt = m_receipt, temp2, temp3;
	int offset = 0;

	os << "Title:\t\t" << m_title << endl;
	os << "Studio:\t\t" << m_studio << endl;
	os << "Year:\t\t" << m_year << endl;

	tempReceipt.erase(remove(tempReceipt.begin(), tempReceipt.end(), ' '), tempReceipt.end());

	for (int i = tempReceipt.length(); i > -1; --i)
	{
		if (i % 3 == 0 && i != 0 && i != tempReceipt.length())
			temp2 += ',';
		temp2 += tempReceipt[tempReceipt.length() - i];
	}

	os << "Adjusted Gross:\t" << "$" << temp2 << endl;

	for (int index = 0; index < m_stars.length(); ++index)
	{
		if (m_stars[index] != ',')
			temp3 += m_stars[index];
		else
			temp3[index - 1 - (offset++)] = ',';
	}
	os << "Stars:\t\t" << temp3 << endl << endl;
}

/* int MovieType::compareTitle(const MovieType& m2) const
	Purpose: Compare the m_title member data of two MovieType objects, m and m2.
	Precondition: m and m2 must be valid
	Postcondition: Either
	1. if m_title > m2.m_title, return 1.
					or
	2. if m_title < m2.m_title, return -1.
*/
int MovieType::compareTitle(const MovieType& m2) const
{
	if (m_title > m2.m_title)
		return 1;
	if (m_title < m2.m_title)
		return -1;
	return 0;
}

/* bool MovieType::operator==(const MovieType& p2) const
	Purpose: Compare the m_title member data of two MovieType objects, m and m2.
	Precondition: m and m2 must be valid
	Postcondition: Either
	1. if m_title == p2.m_title, return true.
					or
	2. if m_title != p2.m_title, return false.
*/
bool MovieType::operator==(const MovieType& m2) const
{
    return m_title == m2.m_title;
}

/* bool MovieType::ReadOneMovieFromFile(ifstream& fin)
	Purpose: Read one block of related movie information from a .txt file and store it in a
	         MovieType variable m
	Precondition: fin must be have opened succesfully.
	Postcondition: m will be initialized with data from the file
*/
bool MovieType::ReadOneMovieFromFile(ifstream& fin)
{
	string temp;
	char value;

	getline(fin, m_title);

	if (m_title == StopName)
		return false;

	fin >> m_year;
	fin.ignore(3);

	getline(fin, m_receipt);
	
	getline(fin, temp);

	size_t comma = temp.find(",");

	m_stars = "None";

	if (comma != string::npos) 
		m_stars = temp.substr(comma + 2);

    m_studio = temp.substr(0, comma);

	return true;
}

/* string MovieType::getTitle() const
	Purpose: Access and return the value of m_title of a MovieType varible
	Precondition: m must be valid
	Postcondition: m_title is returned
*/
string MovieType::getTitle() const
{
	return m_title;
}