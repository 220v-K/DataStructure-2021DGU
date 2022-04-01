

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
		cout << "�߸��� ����� �̸� �Է�" << endl;
	else
	{
		// employee ��� ����
		TreeNode<TE, KF>* subNode = new TreeNode<TE, KF>(employee, NULL, NULL, parent);

		// ������� sub�� ���ٸ� ������� sub�� ����
		if (parent->sub == NULL)
			parent->sub = subNode;
		// ������� sub�� �ϳ��� �ִٸ� sub�� �� ������(rank�� ����) ����� right�� ���ο� employee�� ����.
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
		cout << "�������� �ʴ� ����Դϴ�." << endl;
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
			// victim�� sub ���� �� ������Ŵ
			while (temp->sub != NULL)
			{
				//Node��ü�� �ű�� ���� �ƴ϶�, Key�� �����ϴ� �������
				temp->element.setKey(temp->sub->element.key());
				p = temp;
				temp = temp->sub;
			}
			// ������ų sub�� ��������, right���� �� rank�� �÷���
			while (temp->right != NULL)
			{
				temp->element.setKey(temp->right->element.key());
				p = temp;
				temp = temp->right;
			}
			// ������ ��� ������, �������� sub�� �������״���, right�� rank�� �÷ȴ����� ����
			// ������ ���� ����� ���� ����� ��带 NULL�� ����� delete.
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
	// victim�� �ְ���(sub)�̸�
	else if (victim->employer->sub == victim)
	{
		temp = victim;
		p = temp;
		// victim�� sub ���� �� ������Ŵ
		while (temp->sub != NULL)
		{
			temp->element.setKey(temp->sub->element.key());
			p = temp;
			temp = temp->sub;
		}
		// ������ų sub�� ��������, right���� �� rank�� �÷���
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
	// victim�� sub�� �ƴϸ�
	else
	{
		temp = victim;
		p = temp;
		// victim�� sub ���� �� ������Ŵ
		while (temp->sub != NULL)
		{
			temp->element.setKey(temp->sub->element.key());
			p = temp;
			temp = temp->sub;
		}
		// ������ų sub�� ��������, right���� �� rank�� �÷���
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
			// p�� temp�� ��������
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
	// p�� NULL�� �ƴ� ��
	if (p != NULL)
	{
		// sub���� �� �����
		if(p->sub != NULL)
			clearSub(p->sub);

		// right�� ����
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
	// �ڽ��� ���
	if (p != NULL)
	{
		// ������ level��ŭ +�� ����� �� �̸� ���
		for (int i = 0; i < level; i++)
			cout << "+";
		cout << p->element.key() << endl;

		// �ڽ��� ����� ��, �ڽ��� sub���� ���. level�� +1�ؼ� Recursion.
		if (p->sub != NULL)
			showSub(p->sub, level + 1);

		// �� ����, �ڽ��� �������� (����ְ� ����) employee���� ���
		if (p->right != NULL)
			showSub(p->right, level);
	}
}
