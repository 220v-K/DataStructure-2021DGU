

#include "exprtree.h"
#include <iostream>

using namespace std;
//--------------------------------------------------------------------

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
{
	this->element = elem;
	this->left = leftPtr;
	this->right = rightPtr;
}

//--------------------------------------------------------------------

ExprTree::ExprTree()
{
	root = NULL;
}

ExprTree::~ExprTree()
{
	clear();
}

//--------------------------------------------------------------------

char input;		//input
char inputc[30];
int input_i = 0;

void ExprTree::build()
{
	ExprTreeNode* testNode = new ExprTreeNode('\0', NULL, NULL);	//isFull Check
	if (testNode == NULL)
	{
		cout << "Tree is Full" << endl;
	}
	else
	{
		cout << "AND : * , OR : + , NOT : -" << endl;
		//prefix�� �Է¹޴� �κ�
		int i = 0;
		do
		{
			cin.get(input);
			if (input == '\n')
				break;
			//���� ó��
			if (!(input == '+' || input == '-' || input == '*' || (int)(input - '0') == 0 || (int)(input - '0') == 1 ) )
			{
				cout << "�ùٸ� ���� �Ǵ� �����ڸ� �Է��� �ּ���" << endl;
				build();
				break;
			}

			inputc[i] = input;
			i++;
		} while (input != '\0');

		buildSub(root);
	}
}

void ExprTree::buildSub(ExprTreeNode*& p)
{
	int whatOperator = 0;	//� operator����
	//�ƹ��͵� ������ �װ��� insert
	if (p == NULL)
	{
		p = new ExprTreeNode(inputc[input_i], NULL, NULL);
		if (inputc[input_i] == '+' || inputc[input_i] == '*')	//AND�� OR�� ��
			whatOperator = 1;
		else if (inputc[input_i] == '-')	//NOT�� ��
			whatOperator = 2;
		input_i++;
	}
	//input�� �����ڶ��, left�� right�� insert
	if (whatOperator == 1)
	{
		buildSub(p->left);
		buildSub(p->right);
	}
	else if (whatOperator == 2)
	{
		buildSub(p->right);
	}
}

//--------------------------------------------------------------------

void ExprTree::expression() const
{
	if (root == NULL)
		cout << "Tree is Empty" << endl;
	else
	{
		exprSub(root);
	}
}

void ExprTree::exprSub(ExprTreeNode* p) const
{
	if (p->element == '+' || p->element == '*')
	{
		cout << "(";
		exprSub(p->left);
		cout << p->element;
		exprSub(p->right);
		cout << ")";
	}
	else if (p->element == '-')
	{
		cout << "(";
		cout << p->element;
		exprSub(p->right);
		cout << ")";
	}
	else
		cout << p->element;
}

//--------------------------------------------------------------------

float ExprTree::evaluate() const
{
	if (root == NULL)
	{
		cout << "Tree is Empty" << endl;
		return 0;
	}
	else
	{
		return evaluateSub(root);
	}
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{
	char oper = p->element;

	switch (oper)
	{
	case '*':			//AND
		return (bool)evaluateSub(p->left) && (bool)evaluateSub(p->right);
	case '-':			//NOT
		if (evaluateSub(p->right) == 0)
			return 1;
		else
			return 0;
	case '+':			//OR
		return (bool)evaluateSub(p->left) || (bool)evaluateSub(p->right);	
	default:
		return (float) (p->element-'0');
	}
}

//--------------------------------------------------------------------

void ExprTree::clear()
{
	if (root == NULL)
		cout << "Tree is Empty" << endl;
	else
	{
		clearSub(root);
		root = NULL;
		cout << endl;
	}
}

void ExprTree::clearSub(ExprTreeNode* p)
{
	ExprTreeNode* tempPtr = p;

	//children node�� ���� ��
	if (p->left == NULL && p->right == NULL)
	{
		p = NULL;
		cout << "delete " << tempPtr->element << " ";		//���� �۵� check��..
		delete tempPtr;
	}
	//right���� children node�� ����
	else if (p->left == NULL && p->right != NULL)
	{
		clearSub(p->right);
		p = NULL;
		cout << "delete " << tempPtr->element << " ";
		delete tempPtr;
	}
	//left���� children node�� ����
	else if (p->left != NULL && p->right == NULL)
	{
		clearSub(p->left);
		p = NULL;
		cout << "delete " << tempPtr->element << " ";
		delete tempPtr;
	}
	//children node�� left, right�� �� �� ����
	else if (p->left != NULL && p->right != NULL)
	{
		clearSub(p->left);
		clearSub(p->right);
		p = NULL;
		cout << "delete " << tempPtr->element << " ";
		delete tempPtr;
	}
	else
		cout << "Unexpected error" << endl;
}

//--------------------------------------------------------------------

void ExprTree::showStructure() const
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

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
	int j;

	if (p != 0)
	{
		showSub(p->right, level + 1);
		for (j = 0; j < level; j++)
			cout << "\t";
		cout << " " << p->element;
		if ((p->left != 0) &&
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);
	}
}

