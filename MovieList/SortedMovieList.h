#pragma once
#include "MovieType.h"
const int MAX_LIST = 30; 
typedef MovieType ListItemType;

/*SortedMovieList class
	Purpose: contains a movies[] array of type MovieType
	where the MovieType objects will be stored and a size
	variable where the length of the movies[] array will be
	stored
*/

class SortedMovieList
{
public:
	SortedMovieList();  
	int getLength() const;
	int SortedMovieList::getMAX_LIST() const;
	void ReadAllMoviesFromFile(ifstream& fin, string fname);
	bool insert(int index, ListItemType newItem);
	bool add(const ListItemType& newItem);
	int SortedMovieList::find(const ListItemType& itemToFind)const;
	bool remove(int index); 
	bool findAndRemove(const ListItemType& itemToFind);
	bool retrieve(int index, ListItemType& dataItem) const;
	void display() const;

private:
	ListItemType movies[MAX_LIST]; 
	int size;             
};