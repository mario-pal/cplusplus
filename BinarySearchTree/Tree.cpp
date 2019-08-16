#define _AFXDLL
#include "Tree.h"
#include <string>
#include <iostream>


using namespace std;

/* TreeNode::TreeNode(const Student& student, TreeNode* left, TreeNode* right)
Purpose: initializes TreeNode when given arguments.
Precondition: None.
Postcondition: m_student is set to given values and both pointers are null
*/
TreeNode::TreeNode(const Student& student, TreeNode* left, TreeNode* right)
: m_student(student), m_left(left), m_right(right)
{}

/* Tree::Tree()
Purpose: Initializes m_root to zero when given arguments.
Precondition: None.
Postcondition: m_root is set to null.
*/
Tree::Tree()
: m_root(0)
{}

/* Tree::Tree(const Tree& tree2)
Purpose: Copy constructor that calls public Copy function.
Precondition: tree2 must be valid
Postcondition: Copy(const Tree& tree2) is called.
*/
Tree::Tree(const Tree& tree2)
{
	Copy(tree2);
}

/* void Tree::Copy(const Tree& tree2)
Purpose: Calls private Copy function.
Precondition: tree2 must be valid and sorted.
Postcondition: Copy(const Tree& tree2, TreeNode* m_root) is called.
*/
void Tree::Copy(const Tree& tree2)
{
	Copy(m_root, tree2.m_root);
}

/* void Tree::Copy(TreeNode*&pThis, TreeNode* pTree2)
Purpose: Set the Tree object that called this function equal to the argument.
Precondition: tree2 must be valid and sorted.
Postcondition: A new tree object is successfully copied.
*/
void Tree::Copy(TreeNode*&pThis, TreeNode* pTree2)
{
	if (pTree2 == 0)
		return;

	pThis = new TreeNode(pTree2->m_student, 0, 0);

	Copy(pThis->m_left, pTree2->m_left);
	Copy(pThis->m_right, pTree2->m_right);
}

/* Tree::~Tree()
Purpose: Destructor for Tree objects that calls public clear function.
Precondition: Tree by be initialized.
Postcondition: Clear(TreeNode* pTree) is called
*/
Tree::~Tree()
{
	Clear(m_root);
}

/* void Tree::Clear(TreeNode* pTree)
Purpose: Prevent memory leaks by deleting entire BST.
Precondition: Tree by be initialized and sorted.
Postcondition: Entire BST is deleted.
*/
void Tree::Clear(TreeNode* pTree)
{
	if (pTree == 0)
		return;
	Clear(pTree->m_left);
	Clear(pTree->m_right);
	delete pTree;
}

/* bool Tree::IsEmpty() const
Purpose: Determine is the BST is empty.
Precondition: Tree object must be initialized.
Postcondition: boolean value is returned.
*/
bool Tree::IsEmpty() const
{
	return m_root == 0;
}

/* int Tree::Size() const
Purpose: Call private Size() function.
Precondition: Tree object must be initialized.
Postcondition: An interger value is returned.
*/
int Tree::Size() const
{
	return Size(m_root);
}

/* int Tree::Size() const
Purpose: Determine, through recursion, the actual number of nodes present in the BST.
Precondition: Tree object must be initialized.
Postcondition: Size of the BST is returned as an integer.
*/
int Tree::Size(TreeNode* pTree) const
{
	if (pTree == 0)
		return 0;
	return 1 + Size(pTree->m_left) + Size(pTree->m_right);
}

/* bool Tree::Insert(const Student& student)
Purpose: Call the private bool Insert(const Student& student, TreeNode*& pTree) function.
Precondition: Tree object must be initialized.
Postcondition: boolean value if returned.
*/
bool Tree::Insert(const Student& student)
{
	return Insert(student, m_root);
}

/* bool Tree::Insert(const Student& student, TreeNode*& pTree)
Purpose: Insert node in appropriate place in BST.
Precondition: Student and pTree must be valid.
Postcondition: True is returned is node was added successfully or false otherwise.
*/
bool Tree::Insert(const Student& student, TreeNode*& pTree)
{
	if (pTree == 0)
	{
		pTree = new TreeNode(student, 0, 0);
		return true;
	}

	if (student.getId() < pTree->m_student.getId())	// go left
		return Insert(student, pTree->m_left);
	else if (student.getId() > pTree->m_student.getId())	// go right
		return Insert(student, pTree->m_right);

	return false;
}

/* bool Tree::Delete(int id)
Purpose: Call private bool Delete(int id, TreeNode*& pTree) function.
Precondition: Arument must be an integer value.
Postcondition: bool Delete(int id, TreeNode*& pTree) function is called and boolean value is returned.
*/
bool Tree::Delete(int id)
{
	return Delete(id, m_root);
}

/* bool Tree::Delete(int id, TreeNode*& pTree)
Purpose: Locate matching student in the node based on ID number and then calling DeleteNode(TreeNode*& pTree) to delete the matching entry.
Precondition: id and pTree must be valid and BST must be sorted.
Postcondition: false is returned if the BST is empty. True is returned if DeleteNode was successfully called.
*/
bool Tree::Delete(int id, TreeNode*& pTree)
{
	if (pTree == 0)
		return false;
	else if (id == pTree->m_student.getId())
	{
		DeleteNode(pTree);
		return true;
	}

	else if (id > pTree->m_student.getId())
		return Delete(id, pTree->m_right);
	else if (id < pTree->m_student.getId())
		return Delete(id, pTree->m_left);
}

/* void Tree::DeleteNode(TreeNode*& pTree)
Purpose: Delete selected node.
Precondition: id and pTree must be valid and BST must be sorted.
Postcondition: node is sucessfully deleted.
*/
void Tree::DeleteNode(TreeNode*& pTree)
{
	TreeNode* temp = pTree;

	if (pTree->m_left == 0)
	{
		pTree = pTree->m_right;
		delete temp;
	}
	else if (pTree->m_right == 0)
	{
		pTree = pTree->m_left;
		delete temp;
	}
	else if (pTree->m_left != 0 && pTree->m_right != 0)
	{
		Student myStudent;

		GetPredecessor(myStudent, pTree);

		pTree->m_student = myStudent;

		Delete(myStudent.getId(), pTree->m_left);
	}
}

/* void Tree::GetPredecessor(Student& myStudent, TreeNode* pTree)
Purpose: Store temporary information of the node to be deleted
Precondition: mytudent and pTree must be valid.
Postcondition: myStudent stores the information of m_student that pTree points to.
*/
void Tree::GetPredecessor(Student& myStudent, TreeNode* pTree)
{
	while (pTree->m_right != 0)
		pTree = pTree->m_right;
	myStudent = pTree->m_student;
}

/* bool Tree::Lookup(Student& student) const
Purpose: Call the private bool Tree::Lookup(Student& student, TreeNode* pTree) const function.
Precondition: Student must be valid and Tree object must be initialized.
Postcondition: The private bool Tree::Lookup(Student& student, TreeNode* pTree) const function is called.
*/
bool Tree::Lookup(Student& student) const
{
	return Lookup(student, m_root);
}

/* bool Tree::Lookup(Student& student, TreeNode* pTree) const
Purpose: Search a matching student in the BST by ID.
Precondition: Student and pTree must be valid and Tree object must be initialized and sorted.
Postcondition: False is returned if the BST is empty or thr is returned once the student is found and its data is copied over to the user's Student object.
*/
bool Tree::Lookup(Student& student, TreeNode* pTree) const
{
	if (pTree == 0)
		return false;
	if (pTree->m_student.getId() == student.getId())
	{
		student = pTree->m_student;
		return true;
	}

	if (student.getId() < pTree->m_student.getId())
		return Lookup(student, pTree->m_left);
	else if (student.getId() > pTree->m_student.getId())
		return Lookup(student, pTree->m_right);
}

/* ostream& operator<< (ostream& os, const Tree& tree)
Purpose: To overload << and call the private print function void Print(ostream& os, TreeNode* pTree) const
Precondition: Student must be valid and Tree object must be initialized.
Postcondition: os is returned.
*/
ostream& operator<< (ostream& os, const Tree& tree)
{
	tree.Print(os, tree.m_root);
	return os;
}

/* ostream& operator<<(ostream& os, const TreeNode& n)
Purpose: To overload << and print all the feilds to the screen in the Node in the necessary format.
Precondition: Tree object must be initialized.
Postcondition: os is returned.
*/
ostream& operator<<(ostream& os, const TreeNode& n)
{
	int static count = 0;

	os << "Name: \t" << n.m_student.getName() << endl;
	os << "Age: \t" << n.m_student.getAge() << endl;
	os << "Major: \t" << n.m_student.getMajor() << endl;
	os << "Test: \t";

	for (int cell = 0; cell < 3; cell++)
		os << n.m_student.getTests(cell) << " ";

	os << endl;

	os << "ID: \t" << n.m_student.getId() << endl << endl;

	if (count == 4)
	{
		count = 0;
		cout << "Press ENTER to continue...";
		cin.get();
	}
	count++;
	return os;
}

/* void Tree::Write(TreeNode *tree, ofstream& outFile) const
Purpose: Call the writeToFile function to print the data in the m_student member fields.
Precondition: pTree must be valid Tree object must be initialized and sorted.
Postcondition: void writeToFile(ofstream& os) function is called.
*/
void Tree::Write(TreeNode *tree, ofstream& outFile) const//PRINT/WRITING TO FILE
{
	if (tree == 0)
		return;

	this->Write(tree->m_left, outFile);

	tree->m_student.writeToFile(outFile);

	Write(tree->m_right, outFile);
}

/* void Tree::Print(ostream& os, TreeNode* pTree) const
Purpose: To call public function ostream& operator<<(ostream& os, const TreeNode& n)
Precondition: pTree must be valid Tree object must be initialized and sorted.
Postcondition: os is returned by reference.
*/
void Tree::Print(ostream& os, TreeNode* pTree) const//PRINT TO SCREEN
{
	if (pTree == 0)
		return;

	this->Print(os, pTree->m_left);

	os << *pTree;

	Print(os, pTree->m_right);
}

/* Tree& Tree::operator=(const Tree& tree2)
Purpose: Overload =. Calls the private void Clear(TreeNode* pTree) function and void Copy(const Tree& tree2) function.
Precondition: tree and tree2 must be valid and tree2 must be sorted.
Postcondition: Tree object with its feilds now matching the feilds of tree2 is returned.
*/
Tree& Tree::operator=(const Tree& tree2)
{
	if (this != &tree2)
	{
		Clear(m_root);
		Copy(tree2);
	}
	return *this;
}

/* TreeNode* Tree::getRoot() const
Purpose: Returns the value of m_root of the Tree object that called it.
Precondition: Tree object must be initialized.
Postcondition: The value of m_root is returned.
*/
TreeNode* Tree::getRoot() const
{
	return m_root;
}

void Tree::writeToScreen(const TreeNode& n) const
{
	cout << "Name: \t" << n.m_student.getName() << endl;
	cout << "Age: \t" << n.m_student.getAge() << endl;
	cout << "Major: \t" << n.m_student.getMajor() << endl;
	cout << "Test: \t";

	for (int cell = 0; cell < 3; cell++)
		cout << n.m_student.getTests(cell) << " ";

	cout << endl;

	cout << "ID: \t" << n.m_student.getId() << endl << endl;
}