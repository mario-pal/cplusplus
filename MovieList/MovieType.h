#include "SortedMovieList.h"			
#ifndef __MOVIETYPE_H__
#define __MOVIETYPE_H__

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*MovieType class
	Purpose: To store all information pertaining to a 
	         movie read from a .txt file. It contains 
			 string variables m_title, m_receipt, m_studio,
			 and m_stars that store corresponding information
			 and int variable year that stores the year of the film's release.
			 It also contans functions that are respomsible for manipulating
			 its member data.
*/
class MovieType	
{
	friend ostream& operator<<(ostream& os, const MovieType& p);
private:
	string m_title, m_receipt, m_studio, m_stars;
	int m_year;
public:
	MovieType(string m_title, int m_year, string m_receipts, string m_studio, string m_stars);
	MovieType();
	void Initialize(string m_title, int m_year, string m_receipts, string m_studio, string m_stars);
	void display(ostream& os = cout) const;
	int compareTitle(const MovieType& m2) const;
	bool ReadOneMovieFromFile(ifstream& fin);
	bool operator==(const MovieType& m2) const;
	string getTitle() const;
};

#endif