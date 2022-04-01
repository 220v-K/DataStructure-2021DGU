
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
	if (isFull() == true)		//Tree가 가득 찼을 때 예외
		cout << "Tree is Full" << endl;
	else
		insertSub(root, newElement);
}

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p, const TE& newElement)
{
	//아무것도 없으면 그곳에 insert
	if (p == NULL)
	{
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL);
	}
	//key값이 element > newElement면 왼쪽으로 insertSub
	else if (p->element.key() > newElement.key())
	{
		insertSub(p->left, newElement);
	}
	//key값이 element < newElement면 오른쪽으로 insertSub
	else if (p->element.key() < newElement.key())
	{
		insertSub(p->right, newElement);
	}
	//key값이 element = newElement면 newElement로 교체
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
	//아무것도 없으면 search 실패
	if (p == NULL)
	{
		return false;
	}
	//key값이 element > searchElement면 왼쪽으로 retrieveSub
	else if (p->element.key() > searchKey)
	{
		retrieveSub(p->left, searchKey, searchElement);
	}
	//key값이 element < searchElement면 오른쪽으로 retrieveSub
	else if (p->element.key() < searchKey)
	{
		retrieveSub(p->right, searchKey, searchElement);
	}
	//key값이 element = searchElement면 true 반환 / searchElement(main함수에서 testData)를 p->element로 변경.
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
	//deleteKey와 일치하는 Key를 가진 노드를 찾지 못했을 경우
	if (p == NULL)
	{
		return false;
	}
	//element의 key값 > deleteKey 면 left 노드로
	else if (p->element.key() > deleteKey)
	{
		removeSub(p->left, deleteKey);
	}
	//element의 key값 < deleteKey 면 right 노드로
	else if (p->element.key() < deleteKey)
	{
		removeSub(p->right, deleteKey);
	}
	//삭제할 노드를 찾았을 경우
	else if (p->element.key() == deleteKey)
	{
		BSTreeNode<TE, KF>* tempPtr = p;

		//children node가 없거나, right 1개일 때.
		if (p->left == NULL)
		{
			p = p->right;
			delete tempPtr;
		}
		//children node가 left 1개일 때.
		else if (p->right == NULL)
		{
			p = p->left;
			delete tempPtr;
		}
		//children node가 2개일 때
		else
		{
			//삭제할 노드의 왼쪽에서 가장 오른쪽 노드를 tempPtr로 point
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
	//p의 element를 p의 왼쪽의 rightmost로 변경
	r->element = delPtr->element;
	//p 왼쪽의 rightmost였던 노드의 left가 존재한다면, left를 그 자리에 넣음. left가 존재하지 않는다면, 그냥 삭제.
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
	//children node가 없을 때
	if (p->left == NULL && p->right == NULL)
	{
		cout << p->element.key() << " ";
	}
	//right에만 children node가 존재
	else if (p->left == NULL && p->right != NULL)
	{
		cout << p->element.key() << " ";
		writeKeysSub(p->right);
	}
	//left에만 children node가 존재
	else if (p->left != NULL && p->right == NULL)
	{
		writeKeysSub(p->left);
		cout << p->element.key() << " ";
	}
	//children node가 left, right에 둘 다 존재
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

	//children node가 없을 때
	if (p->left == NULL && p->right == NULL)
	{
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";		//정상 작동 check용..
		delete tempPtr;
	}
	//right에만 children node가 존재
	else if (p->left == NULL && p->right != NULL)
	{
		clearSub(p->right);
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";
		delete tempPtr;
	}
	//left에만 children node가 존재
	else if (p->left != NULL && p->right == NULL)
	{
		clearSub(p->left);
		p = NULL;
		cout << "delete " << tempPtr->element.key() << " ";
		delete tempPtr;
	}
	//children node가 left, right에 둘 다 존재
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