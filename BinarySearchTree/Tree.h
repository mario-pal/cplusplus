#define _AFXDLL
//#include <afxwin.h>
#include "Student.h"
#include <fstream>

using namespace std;

//#define new DEBUG_NEW

/*TreeNode struct
Purpose: To store all information pertaining to an
object in a node in a binary search tree. It contains
variable m_student of type Student that stores the student object
and TreeNode* variable m_left and m_right that make it like a tree.
It also contans a function that is respomsible for initializing
its data.
*/

struct TreeNode
{
	Student m_student;
	TreeNode* m_left;
	TreeNode* m_right;
	TreeNode(const Student& student, TreeNode* left = NULL, TreeNode* right = NULL);
};

ostream& operator<<(ostream&, const TreeNode&);

class Tree
{
	friend ostream& operator<< (ostream& os, const Tree& tree);
public:
	Tree();
	Tree(const Tree& tree2);
	~Tree();

	bool IsEmpty() const;
	int Size() const;
	bool Insert(const Student& student);
	bool Delete(int id);
	bool Lookup(Student& student) const;
	void Write(TreeNode *tree, ofstream& outFile) const;
	void writeToScreen(const TreeNode& n) const;
	TreeNode* getRoot() const;

	Tree& operator=(const Tree& tree2);
private:
	TreeNode* m_root;

	bool Insert(const Student& student, TreeNode*& pTree);
	int Size(TreeNode* pTree) const;

	void Print(ostream& os, TreeNode* pTree) const;

	bool Lookup(Student& student, TreeNode* pTree) const;

	bool Delete(int id, TreeNode*& pTree);
	void DeleteNode(TreeNode*& pTree);

	void Print(TreeNode* pTree) const;

	void Clear(TreeNode* pTree);
	void Copy(const Tree& list2);
	void Copy(TreeNode*& pThis, TreeNode* pTree2);

	void GetPredecessor(Student& myStudent, TreeNode* pTree);
};
