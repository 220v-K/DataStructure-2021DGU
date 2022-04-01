
#include <iostream>
#include "bstree.h"

using namespace std;

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE& elem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	this->element = elem;
	this->left = leftPtr;
	this->right = rightPtr;
}

template < class TE, class KF >
BSTree<TE, KF>::BSTree()
{
	root = NULL;
}

template < class TE, class KF >
BSTree<TE, KF>::~BSTree()
{
	clear();
}

// Insert

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE& newElement)
{
	if (isFull() == true)		//Tree�� ���� á�� �� ����
		cout << "Tree is Full" << endl;
	else
		insertSub(root, newElement);
}

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement)
{
	//�ƹ��͵� ������ �װ��� insert
	if (p == NULL)
	{
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL);
	}
	//key���� element > newElement�� �������� insertSub
	else if (p->element.key() > newElement.key())
	{
		insertSub(p->left, newElement);
	}
	//key���� element < newElement�� ���������� insertSub
	else if (p->element.key() < newElement.key())
	{
		insertSub(p->right, newElement);
	}
	//key���� element = newElement�� newElement�� ��ü
	else if (p->element.key() == newElement.key())
	{
		p->element = newElement;
	}
	else
		cout << "Unexpected error" << endl;
}

//--------------------------------------------------------------------

// Retrieve 

template < class TE, class KF >
bool BSTree<TE, KF>::retrieve(KF searchKey, TE& searchElement) const
{
	if (isEmpty() == true)
		return false;
	else
		retrieveSub(root, searchKey, searchElement);
}

template < class TE, class KF >
bool BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF>* p, KF searchKey, TE& searchElement) const
{
	//�ƹ��͵� ������ search ����
	if (p == NULL)
	{
		return false;
	}
	//key���� element > searchElement�� �������� retrieveSub
	else if (p->element.key() > searchKey)
	{
		retrieveSub(p->left, searchKey, searchElement);
	}
	//key���� element < searchElement�� ���������� retrieveSub
	else if (p->element.key() < searchKey)
	{
		retrieveSub(p->right, searchKey, searchElement);
	}
	//key���� element = searchElement�� true ��ȯ / searchElement(main�Լ����� testData)�� p->element�� ����.
	else if (p->element.key() == searchKey)
	{
		searchElement = p->element;
		return true;
	}
	else
		cout << "Unexpected error" << endl;
}

//--------------------------------------------------------------------

// Remove

template < class TE, class KF >
bool BSTree<TE, KF>::remove(KF deleteKey)
{
	if (isEmpty() == true)
		return false;
	else
		removeSub(root, deleteKey);
}

template < class TE, class KF >
bool BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF>*& p, KF deleteKey)
{
	//deleteKey�� ��ġ�ϴ� Key�� ���� ��带 ã�� ������ ���
	if (p == NULL)
	{
		return false;
	}
	//element�� key�� > deleteKey �� left ����
	else if (p->element.key() > deleteKey)
	{
		removeSub(p->left, deleteKey);
	}
	//element�� key�� < deleteKey �� right ����
	else if (p->element.key() < deleteKey)
	{
		removeSub(p->right, deleteKey);
	}
	//������ ��带 ã���� ���
	else if (p->element.key() == deleteKey)
	{
		BSTreeNode<TE, KF>* tempPtr = p;

		//children node�� ���ų�, right 1���� ��.
		if (p->left == NULL)
		{
			p = p->right;
			delete tempPtr;
		}
		//children node�� left 1���� ��.
		else if (p->right == NULL)
		{
			p = p->left;
			delete tempPtr;
		}
		//children node�� 2���� ��
		else
		{
			//������ ����� ���ʿ��� ���� ������ ��带 tempPtr�� point
			tempPtr = p->left;
			while (tempPtr->right != NULL)
			{
				tempPtr = tempPtr->right;
			}

			//cutRightmost
			cutRightmost(p, tempPtr);
		}
		return true;
	}
	else
		cout << "Unexpected error" << endl;
}

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF>*& r, BSTreeNode<TE, KF>*& delPtr)
{
	//p�� element�� p�� ������ rightmost�� ����
	r->element = delPtr->element;
	//p ������ rightmost���� ����� left�� �����Ѵٸ�, left�� �� �ڸ��� ����. left�� �������� �ʴ´ٸ�, �׳� ����.
	removeSub(r->left, delPtr->element.key());
}

//--------------------------------------------------------------------

// Write Keys

template < class TE, class KF >
void BSTree<TE, KF>::writeKeys() const
{
	if (isEmpty() == true)
		cout << "Tree is Empty" << endl;
	else
		writeKeysSub(root);
}

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF>* p) const
{
	//children node�� ���� ��
	if (p->left == NULL && p->right == NULL)
	{
		cout << p->element.key() << " ";
	}
	//right���� children node�� ����
	else if (p->left == NULL && p->right != NULL)
	{
		cout << p->element.key() << " ";
		writeKeysSub(p->right);
	}
	//left���� children node�� ����
	else if (p->left != NULL && p->right == NULL)
	{
		writeKeysSub(p->left);
		cout << p->element.key() << " ";
	}
	//children node�� left, right�� �� �� ����
	else if (p->left != NULL && p->right != NULL)
	{
		writeKeysSub(p->left);
		cout << p->element.key() << " ";
		writeKeysSub(p->right);
	}
	else
		cout << "Unexpected error" << endl;
}

//--------------------------------------------------------------------

// Clear

template < class TE, class KF >
void BSTree<TE, KF>::clear()
{
	if (isEmpty() == true)
		cout << "Tree is Empty" << endl;
	else
	{
		clearSub(root);
		root = NULL;
		cout << endl;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)
{
	BSTreeNode<TE, KF>* tempPtr = p;

	//children node�� ���� ��
	if (p->left == NULL && p->right == NULL)
	{
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";		//���� �۵� check��..
		delete tempPtr;
	}
	//right���� children node�� ����
	else if (p->left == NULL && p->right != NULL)
	{
		clearSub(p->right);
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";
		delete tempPtr;
	}
	//left���� children node�� ����
	else if (p->left != NULL && p->right == NULL)
	{
		clearSub(p->left);
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";
		delete tempPtr;
	}
	//children node�� left, right�� �� �� ����
	else if (p->left != NULL && p->right != NULL)
	{
		clearSub(p->left);
		clearSub(p->right);
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";
		delete tempPtr;
	}
	else
		cout << "Unexpected error" << endl;
}

//--------------------------------------------------------------------

// Empty / Full

template < class TE, class KF >
bool BSTree<TE, KF>::isEmpty() const
{
	if (root == NULL)
		return true;
	else
		return false;
}

template < class TE, class KF >
bool BSTree<TE, KF>::isFull() const
{
	TE test;
	BSTreeNode<TE, KF>* testNode = new BSTreeNode<TE, KF>(test ,NULL ,NULL);

	if (testNode == NULL)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

// Show Structure

template < class TE, class KF >
void BSTree<TE, KF>::showStructure() const

{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF>* p, int level) const

{
	int j;   // Loop counter

	if (p != 0)
	{
		showSub(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->element.key();   // Output key
		if ((p->left != 0) &&           // Output "connector"
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);          // Output left subtree
	}
}

// In-lab operations
template <class TE, class KF>
int BSTree<TE, KF>::getHeight() const
{
	if (isEmpty() == true)
		return 0;
	else
		return getHeightSub(root) + 1;
}

template <class TE, class KF>
int BSTree<TE, KF>::getHeightSub(BSTreeNode<TE, KF>* p) const
{
	int leftheight = 0, rightheight = 0;

	if(p->left != NULL)
		leftheight = getHeightSub(p->left) + 1;
	if(p->right != NULL)
		rightheight = getHeightSub(p->right) + 1;

	if (leftheight > rightheight)
		return leftheight;
	else
		return rightheight;
}