#define _AFXDLL
#include "PhoneBook.h"
#include <iostream>
#include <string>

using namespace std;

/* PhoneBookItem::PhoneBookItem(const string& name, int age, const string& phone, PhoneBookItem *next)
Purpose: Constructor that initializes name and phone to "", ints to 0 and next pointer to null for next link
list node.
*/
PhoneBookItem::PhoneBookItem(const string& name, int age, const string& phone, PhoneBookItem *next)
: m_name(name), m_age(age), m_phone(phone), m_next(next)
{}

/* PhoneBook::PhoneBook()
Purpose: Constructor that makes m_head pointer point to dummy node to start the link list
*/
PhoneBook::PhoneBook()
: m_head(new PhoneBookItem("", -99, "", nullptr)), m_num(0)
{}

/* PhoneBook::PhoneBook()
Purpose: Copy Constructor
*/
PhoneBook::PhoneBook(const PhoneBook& existingPB)
{
	Copy(existingPB);
}

/* PhoneBook::PhoneBook()
Purpose: Destructor that calls the Clear() function.
*/
PhoneBook::~PhoneBook()
{
	Clear();
}

/* ostream& operator<< (ostream& os, const PhoneBookItem& n)
Purpose: Oveloading operator "<<" so that cout << n can be called by
another overloading oprator PhoneBook member function, member << operator
*/
ostream& operator<< (ostream& os, const PhoneBookItem& n)	
{
	os << "Name:\t" << n.m_name << "\nAge:\t" << n.m_age << "\nPhone:\t" << n.m_phone <<endl<<endl;
	return os;
}

/* PhoneBook& PhoneBook::operator =(const PhoneBook& pb2) 
Purpose: Oveloading operator "=" so one linked list can be copied over to another 
*/
PhoneBook& PhoneBook::operator =(const PhoneBook& pb2)  // list1 = list2;
{
	if (this != &pb2)
	{
		Clear();
		Copy(pb2);
	}

	return *this;
}

/* bool PhoneBook::IsEmpty() const
Purpose: Determine if the linked list is empty
Precondition: none
Postcondition: return boolean value
*/
bool PhoneBook::IsEmpty() const
{
	return m_num == 0;
	//or return m_head->m_next == NULL;
}

/* int PhoneBook::Size() const
Purpose: Return the current size of the linked list
Precondition: none
Postcondition: return m_num
*/
int PhoneBook::Size() const
{
	return m_num;
}

/* bool PhoneBook::Insert(const string& name, const int age, const string& phone)
Purpose: Insert a new PhoneBookItem in alphabetical order
Precondition: PhoneBook list must be valid and name must have a value by user
Postcondition: Either
			   New PhoneBookItem node is added to the link list and true
			   is returned.
									or
			   Name entered matches the name field of PhoneBookItem already
			   in the linked list and false is returned.
*/
bool PhoneBook::Insert(const string& name, const int age, const string& phone)
{
	PhoneBookItem *p = m_head->m_next;
	PhoneBookItem *tp = m_head;	

	if (m_head->m_next == 0)
	{
		m_head->m_next = new PhoneBookItem(name, age, phone, m_head->m_next);
		m_num++;
		return true;
	}

	while (p != 0)
	{
		if (name == p->m_name)
			return false;
		else if (name < p->m_name)
			break;
		tp = p;
		p = p->m_next;
	}

	p = m_head->m_next;
	tp = m_head;

	while (p != 0)
	{
		if (name < p->m_name)
		{
			tp->m_next = new PhoneBookItem(name, age, phone, p);
			m_num++;
			return true;
		}
		tp = p;
		p = p->m_next;
	}

	tp->m_next = new PhoneBookItem(name, age, phone, p);
	m_num++;
	return true;
}

/* bool PhoneBook::Delete(const string& name)
Purpose: Delete a PhoneBookItem (node) from linked list
Precondition: Linked list must be valid and sorted
Postcondition: Either
Entered name matches a PhoneBookItem's name field and true
is returned.
						or
Name entered does not match any PhoneBookItem's name field
and false is returned.
*/
bool PhoneBook::Delete(const string& name)
{
	PhoneBookItem *p = m_head->m_next;
	PhoneBookItem *tp = m_head;			

	while (p != 0)
	{
		if (name < p->m_name)
			break;
		else if (name == p->m_name)
		{
			tp->m_next = p->m_next;
			delete p;
			m_num--;
			return true;
		}
		tp = p;
		p = p->m_next;
	}

	return false;
}

/* bool PhoneBook::Lookup(const string& name, int& age, string& phone) const 
Purpose: Search for a specific PhoneBookItem by searching for a matching name field.
Precondition: Linked list must be valid and sorted
Postcondition: Either
Entered name matches a PhoneBookItem's name field and true
is returned.
						or
Name entered does not match any PhoneBookItem's name field
and false is returned.
*/
bool PhoneBook::Lookup(const string& name, int& age, string& phone) const 
{
	PhoneBookItem *p = m_head->m_next;
	while (p != 0)
	{
		if (name < p->m_name)
			break;
		if (name == p->m_name)
		{
			age = p->m_age;
			phone = p->m_phone;
			return true;
		}

		p = p->m_next;
	}
	return false;
}

/* ostream& operator<< (ostream& os, const PhoneBook& pb)
Purpose: Oveloading operator "<<".
Calls public "<<" overloded function.
*/
ostream& operator<< (ostream& os, const PhoneBook& pb) // cout << list;
{
	PhoneBookItem *p = pb.m_head->m_next; // skip dummy node
	int count = 0;
	while (p != 0)
	{
		cout << *p << endl;
		p = p->m_next;
		count++;
		if (count == 4)
		{
			count = 0;
			cout << "Press enter to continue..." << endl;
			cin.get();
		}
	}

	return os;
}

/* void PhoneBook::Clear()
Purpose: Delete unused linked list to prevent memory leaks.
Precondition: Link list must be valid and have dummy node at least.
Postcondition: Selected linked list is deleted.
*/
void PhoneBook::Clear()
{
	PhoneBookItem *p = m_head; // start with dummy node
	while (p != 0)
	{
		// do something
		PhoneBookItem *save = p;
		p = p->m_next;
		delete save;
	}
}

/* void PhoneBook::Copy(const PhoneBook& list)
Purpose: Help the copy constructor copy one one linked list to a seperate blank slate. 
Precondition: PhoneBook list must be valid
Postcondition: New linked list will have the same values as the copied linked list.
*/
void PhoneBook::Copy(const PhoneBook& list)
{
	PhoneBookItem *p = list.m_head->m_next;
	PhoneBookItem *pThis = m_head = new PhoneBookItem("", -99, "", 0); // create dummy node
	while (p != 0)
	{
		// create a copy of node pointed to by p, and link up
		pThis->m_next = new PhoneBookItem(p->m_name, p->m_age, p->m_phone, 0); 

		// update pointers
		p = p->m_next;
		pThis = pThis->m_next;
	}
	m_num = list.m_num;
}

/* int PhoneBook::GetMaxAge() const
Purpose: Return the max age found in the linked list 
Precondition: PhoneBook list must be valid and sorted
Postcondition: A max age int will be found and returned
*/
int PhoneBook::GetMaxAge() const
{
	PhoneBookItem *p = m_head->m_next;
	int age = -1;

	//age = p->m_age;

	//p = p->m_next;

	while (p != 0)
	{
		if (age < p->m_age)
			age = p->m_age;

		p = p->m_next;
	}

	return age;
}

/* PhoneBook PhoneBook::GetPeopleWithGivenAge(int age) const
Purpose: Create a new PhoneBook called save that only copies the nodes in the existing list
         that match the user inputted age.
Precondition: PhoneBook list must be valid and sorted
Postcondition: PhoneBook save will be returned.
*/
PhoneBook PhoneBook::GetPeopleWithGivenAge(int age) const
{
	PhoneBook save;

	PhoneBookItem *p = m_head->m_next;

	while (p != 0)
	{
		if (age == p->m_age)
			save.Insert(p->m_name, p->m_age, p->m_phone);

		p = p->m_next;
	}

	return save;
}
