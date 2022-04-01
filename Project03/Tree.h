
using namespace std;

template < class TE, class KF > class Tree;
template < class TE, class KF > class TreeNode;

template < class TE, class KF >
class TreeNode             // Facilitator class for the Tree class
{
private:

	// Constructor
	TreeNode(const TE& elem, TreeNode* right, TreeNode* sub, TreeNode* employer);

	// Data members
	TE element;          

	// right : ���� ������� ���� ����� ������ ������(~ �� �ܰ� ���� ���)
	// sub : �ڽ��� ����� ����� ������ rank(seniority)�� ���� ���� ���
	TreeNode *right, *sub, *employer;

	friend class Tree<TE, KF>;
};

//--------------------------------------------------------------------

template < class TE, class KF >    // TE : tree element
class Tree                         // KF : key field
{
public:

	// Constructor
	Tree();

	// Destructor
	~Tree();

	// Tree manipulation operations
	void CEO(const TE& ceo);
	void hire(const TE& employer, const TE& employee);
	void fire(const TE& victimElem);
	void clear();                                // Clear tree

	// Tree status operations
	bool isEmpty() const;                           // Tree is empty

	// Output the tree structure
	void showStructure() const;




private:

	// Find member
	TreeNode<TE, KF>* find(const TE& elem);
	TreeNode<TE, KF>* findEmployer(const TE& elem);

	// Recursive partners
	void clearSub(TreeNode<TE, KF>* p);
	void showSub(TreeNode<TE, KF>* p, int level) const;
	TreeNode<TE, KF>* findSub(const TE& elem, TreeNode<TE, KF>*& root);
	TreeNode<TE, KF>* findEmployerSub(const TE& elem, TreeNode<TE, KF>*& root);


	// Data member
	TreeNode<TE, KF>* root;   // Pointer to the root node
};