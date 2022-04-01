

#include <iostream>
#include "Tree.h"

using namespace std;

template < class TE, class KF >
TreeNode<TE, KF>::TreeNode(const TE& elem, TreeNode* right, TreeNode* sub, TreeNode* employer)
{
	element = elem;
	this->right = right;
	this->sub = sub;
	this->employer = employer;
}

template < class TE, class KF >
Tree<TE, KF>::Tree()
	: root(NULL)
{
}

template < class TE, class KF >
Tree<TE, KF>::~Tree()
{
	clear();
}

//--------------------------------------------------------------------
// Find Member

template < class TE, class KF >
TreeNode<TE, KF>* Tree<TE, KF>::find(const TE& elem)
{
	if (isEmpty() == false)
		return findSub(elem, root);
	else
		return NULL;
}

template < class TE, class KF >
TreeNode<TE, KF>* Tree<TE, KF>::findSub(const TE& elem, TreeNode<TE,KF>*& root)
{
	TreeNode<TE, KF>* p;
	if (root->element.key() == elem.key())
	{
		return root;
	}
	else
	{
		if (root->right != NULL)
		{
			p = findSub(elem, root->right);
			if (p != NULL)
				return p;
		}
		if (root->sub != NULL)
		{
			p = findSub(elem, root->sub);
			if (p != NULL)
				return p;
		}
	}
	return NULL;
}

//--------------------------------------------------------------------
// Hire, Fire part

template < class TE, class KF >
void Tree<TE, KF>::CEO(const TE& ceo)
{
	TreeNode<TE, KF>* ceoNode = new TreeNode<TE, KF>(ceo, NULL, NULL, NULL);
	root = ceoNode;
}

template < class TE, class KF >
void Tree<TE, KF>::hire(const TE& employer, const TE& employee)
{
	TreeNode<TE, KF>* parent;
	parent = find(employer);

	if (parent == NULL)
		cout << "잘못된 고용주 이름 입력" << endl;
	else
	{
		// employee 노드 생성
		TreeNode<TE, KF>* subNode = new TreeNode<TE, KF>(employee, NULL, NULL, parent);

		// 고용주의 sub가 없다면 고용주의 sub로 설정
		if (parent->sub == NULL)
			parent->sub = subNode;
		// 고용주의 sub가 하나라도 있다면 sub중 맨 오른쪽(rank가 낮은) 노드의 right를 새로운 employee로 설정.
		else
		{
			TreeNode<TE, KF>* left = parent->sub;
			while (left->right != NULL)
				left = left->right;
			left->right = subNode;
		}
	}
}

template < class TE, class KF >
void Tree<TE, KF>::fire(const TE& victimElem)
{
	TreeNode<TE, KF>* victim = find(victimElem);
	TreeNode<TE, KF>* p=NULL;
	TreeNode<TE, KF>* temp;

	if (victim == NULL)
	{
		cout << "존재하지 않는 사원입니다." << endl;
		return;
	}
	if (victim == root)
	{
		if (victim->sub == NULL)
		{
			delete victim;
			root = NULL;
		}
		else
		{
			temp = victim;
			// victim의 sub 따라 쭉 승진시킴
			while (temp->sub != NULL)
			{
				//Node자체를 옮기는 것이 아니라, Key를 복사하는 방식으로
				temp->element.setKey(temp->sub->element.key());
				p = temp;
				temp = temp->sub;
			}
			// 승진시킬 sub가 없어지면, right따라 쭉 rank를 올려줌
			while (temp->right != NULL)
			{
				temp->element.setKey(temp->right->element.key());
				p = temp;
				temp = temp->right;
			}
			// 승진이 모두 끝나면, 마지막에 sub를 승진시켰는지, right의 rank를 올렸는지에 따라
			// 마지막 승진 대상의 지울 연결된 노드를 NULL로 만들고 delete.
			if (p->sub == temp)
			{
				p->sub = NULL;
				delete temp;
			}
			else if (p->right == temp)
			{
				p->right = NULL;
				delete temp;
			}
			else
			{
				p->employer->sub = NULL;
				delete temp;
			}
		}
	}
	// victim이 최고참(sub)이면
	else if (victim->employer->sub == victim)
	{
		temp = victim;
		p = temp;
		// victim의 sub 따라 쭉 승진시킴
		while (temp->sub != NULL)
		{
			temp->element.setKey(temp->sub->element.key());
			p = temp;
			temp = temp->sub;
		}
		// 승진시킬 sub가 없어지면, right따라 쭉 rank를 올려줌
		while (temp->right != NULL)
		{
			temp->element.setKey(temp->right->element.key());
			p = temp;
			temp = temp->right;
		}

		if (p->sub == temp)
		{
			p->sub = NULL;
			delete temp;
		}
		else if (p->right == temp)
		{
			p->right = NULL;
			delete temp;
		}
		else
		{
			p->employer->sub = NULL;
			delete temp;
		}
	}
	// victim이 sub가 아니면
	else
	{
		temp = victim;
		p = temp;
		// victim의 sub 따라 쭉 승진시킴
		while (temp->sub != NULL)
		{
			temp->element.setKey(temp->sub->element.key());
			p = temp;
			temp = temp->sub;
		}
		// 승진시킬 sub가 없어지면, right따라 쭉 rank를 올려줌
		while (temp->right != NULL)
		{
			temp->element.setKey(temp->right->element.key());
			p = temp;
			temp = temp->right;
		}

		if (p->sub == temp)
		{
			p->sub = NULL;
			delete temp;
		}
		else if (p->right == temp)
		{
			p->right = NULL;
			delete temp;
		}
		else
		{
			// p를 temp의 왼쪽으로
			p = p->employer->sub;
			while (p->right != temp)
				p = p -> right;

			if (temp->right == NULL)
				p->right = NULL;
			else
				p->right = temp->right;

			delete temp;
		}
	}
}

//--------------------------------------------------------------------

// Clear

template < class TE, class KF >
void Tree<TE, KF>::clear()
{
	if (isEmpty() == true)
		cout << "Already cleared!" << endl;
	else
		clearSub(root);
}

template < class TE, class KF >
void Tree<TE, KF>::clearSub(TreeNode<TE, KF>* p)
{
	// p가 NULL이 아닐 때
	if (p != NULL)
	{
		// sub부터 싹 지우고
		if(p->sub != NULL)
			clearSub(p->sub);

		// right도 지움
		if(p->right != NULL)
			clearSub(p->right);

		delete p;
	}
}

//--------------------------------------------------------------------

// Empty

template < class TE, class KF >
bool Tree<TE, KF>::isEmpty() const
{
	if (root == NULL)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

// Show Structure

template < class TE, class KF >
void Tree<TE, KF>::showStructure() const

{
	if (root == 0)
		cout << " [Empty] " << endl;
	else
		showSub(root, 0);
}

template < class TE, class KF >
void Tree<TE, KF>::showSub(TreeNode<TE, KF>* p, int level) const

{
	// 자신을 출력
	if (p != NULL)
	{
		// 내려간 level만큼 +를 출력한 후 이름 출력
		for (int i = 0; i < level; i++)
			cout << "+";
		cout << p->element.key() << endl;

		// 자신을 출력한 후, 자신의 sub부터 출력. level은 +1해서 Recursion.
		if (p->sub != NULL)
			showSub(p->sub, level + 1);

		// 그 다음, 자신의 오른쪽의 (고용주가 같은) employee들을 출력
		if (p->right != NULL)
			showSub(p->right, level);
	}
}
