#include "SortedMovieList.h"  

/* SortedMovieList::SortedMovieList()
Purpose: no argument constructor to initialize size
Precondition: None.
Postcondition: size = 0
*/
SortedMovieList::SortedMovieList() 
: size(0) 
{
}   

/*  int SortedMovieList::getLength() const
	Purpose: Determines the length of a movies[]. 
	Precondition: None. 
    Postcondition: Returns the number of items 
    that are currently in the list. 
*/
int SortedMovieList::getLength() const
{
	return size;
}

/*  int SortedMovieList::getMAX_LIST() const
	Purpose: Return max length movies[] array can be. 
	Precondition: None. 
    Postcondition: Returns the number of items 
    that are currently in the list. 
*/
int SortedMovieList::getMAX_LIST() const
{
	return MAX_LIST;
}

/*bool SortedMovieList::insert(int index, ListItemType newItem)
   Purpose: Inserts an item into the list at position index.
   Precondition: index indicates the position at which
   the item should be inserted in the list and newItem must be valid
   Postcondition: Either
				  If insertion is successful, newItem is
				  at position index in the list, and other movies are
				  renumbered accordingly, and true is returned
				            or
			      Insertion is not successful and false is returned.
*/
bool SortedMovieList::insert(int index, ListItemType newItem)
{
	if (index < 0 || index > size || size == MAX_LIST)
		return false; 

	for (int pos = size; pos > index; --pos)
		movies[pos] = movies[pos - 1];
     
	movies[index] = newItem;

	++size;  

	return true;
}

/*bool SortedMovieList::add(const ListItemType& newItem)
   Purpose: Add new MovieType object to the movies[] array in alphabetical order according to their titles.
   Precondition: newItem is a valid MovieType
   Postcondition: Either
	1.	There is room in the list, MovieType object is added alphabetically, and true is returned.
						or
	2.	The list is full and false is returned.
*/
bool SortedMovieList::add(const ListItemType& newItem)
{
	if (size == MAX_LIST)
		return false;

	for (int index = 0; index < size; index++)
	{
		if (newItem.compareTitle(movies[index]) == -1)
		{
			insert(index, newItem);
			return true;
		}
	}
}

/*bool SortedMovieList::remove(int index)
	Purpose: Deletes an item from the list at a given position. 
	Precondition: index indicates where the deletion should occur. 
    Postcondition: Either
					The item at position index in the list is 
					deleted, other items are renumbered accordingly, 
					true is returned
							or
					false is returned.
*/
bool SortedMovieList::remove(int index)
{
	if (index < 0 || index >= size)
		return false;

	for (int pos = index; pos < size - 1; ++pos)
		movies[pos] = movies[pos + 1];

	--size;

	return true;
}
/*bool SortedMovieList::retrieve(int index, ListItemType& dataItem) const
	 Purpose: Retrieves a list movie in a specific position. 
	 Precondition: Index is the position of the movie to be retrieved. 
	 Postcondition: Either 
					dataItem is the value of the desired item and 
					true is returned
								or
					false is returned. 
*/
bool SortedMovieList::retrieve(int index, ListItemType& dataItem) const
{
	if (index < 0 || index >= size)
		return false;

	dataItem = movies[index];

	return true;
}

/*void SortedMovieList::ReadAllMoviesFromFile(ifstream& fin, string fname)
	Purpose: Store seperate movie informatio as MovieType objects 
			 and afterwards adding MovieType objects 
			 in alphabetical order (by title) in the movies[] array
	Precondition: fin was opened successfully.
	Postcondition: movies[] array stores up to 10 MovieType objects
*/
void SortedMovieList::ReadAllMoviesFromFile(ifstream& fin, string fname)
{
	MovieType m;
	int index = 0;

	cout << "\nReading file...";
    
	while (m.ReadOneMovieFromFile(fin))
	{

		for (index; index < size; index++)
		{
			if (m.compareTitle(movies[index]) == -1)
				break;
		}

		insert(index, m);

		index = 0;
	}

	cout << "\n\nFinished reading file.\n\n"<<"Press any button to continue...";
	cin.get();
}

/*  void SortedMovieList::display() const
	Purpose: Print all MovieType objects in the movies[] array
	Precondition: The list is valid.
	Postcondition: The list is displayed to cout.
*/
void SortedMovieList::display() const
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		cout << movies[i];
		count++;
		if (count == 3)
		{
			count = 0;
			cout << "Press enter to continue..."<<endl;
			cin.get();
		}
	}
}

/*int SortedMovieList::find(const ListItemType& itemToFind) const
   Precondition: itemToFind.m_title is valid.
   Postcondition: Either
	1.	If there is an item in the list whose id matches
		itemToFind.m_title - the index of the match is returned.
						or
	2.	No item in the list matches itemToFind.m_titile - -1 is returned.
*/
int SortedMovieList::find(const ListItemType& itemToFind) const
{
	int index = 0;

	for (index; index < size; index++)
	{
		if (itemToFind.getTitle() < movies[index].getTitle())
			return -1;
		else if (itemToFind.getTitle() == movies[index].getTitle())
			return index;
	}
}

/*bool SortedMovieList::findAndRemove(const ListItemType& itemToFind)
    Purpose: Combine the find function and remove function to remove 
	         MovieType object at a given index.
	Precondition: itemToFind.m_title is valid.
	Postcondition: Either
	    1.	If fhere is a movie in the list whose title matches
			itemToFind.m_title, the matching item is removed from
			the list and true is returned.
					or
		2.	No movie in the list matches itemToFind.m_title,
			false is returned
*/
bool SortedMovieList::findAndRemove(const ListItemType& itemToFind)
{
	int index = find(itemToFind);
	if (index == -1)
		return false;

	return remove(index);
}
