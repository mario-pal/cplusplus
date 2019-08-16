#define _AFXDLL
#include <afxwin.h>
#include <iostream>

using namespace std;

#define new DEBUG_NEW

/*PhoneBookItem struct
Purpose: To store the data that makes up each
"entry" (node) of the phone book. This data includes
m_name (thats stores the person's name), m_age 
(that stores the person's age) and m_phone
(that stores the person's phone number).
*/
struct PhoneBookItem//NODE
{
	string m_name;
	int m_age;
	string m_phone;

	PhoneBookItem* m_next;

	//like Node(const string& name, int age, Node* next = NULL);
	PhoneBookItem(const string& name, const int age, const string& phone, PhoneBookItem *next = 0);
};

ostream& operator<< (ostream&, const PhoneBookItem&);

/*PhoneBook class
Purpose: To store the private header pointer of type
PhoneBookItem and to store the size of the linked list
in int variable m_num. Functions that manipulate member data
are also included.
*/
class PhoneBook
{
	friend ostream& operator<< (ostream&, const PhoneBook&);
public:
	PhoneBook();
	PhoneBook(const PhoneBook& existingList);

	~PhoneBook();											

	bool IsEmpty() const;
	int Size() const;
	bool Insert(const string& name, int age, const string& phone);
	bool Delete(const string& name);						
	bool Lookup(const string& name, int& age, string& phone) const;		
	int GetMaxAge() const;
	PhoneBook GetPeopleWithGivenAge(int age) const;

	PhoneBook& operator =(const PhoneBook& list2);			


private:
	PhoneBookItem* m_head;   
	int m_num;   
	// IN CLASS EXAMPLE, m_num IS NOT MAINTAINED PROPERLY

	void Clear();											
	void Copy(const PhoneBook& list2);
};