
#include <iostream>
#include "listdbl.h"

using namespace std;

//ListNode�� Constructor
template < class DT >
ListNode<DT>::ListNode(const DT& data, ListNode* priorPtr, ListNode* nextPtr)
{
	this->dataItem = data;
	this->next = priorPtr;
	this->prior = nextPtr;
}

// Constructor
template < class DT >
List<DT>::List(int ignored)
{
	head = NULL;
	cursor = NULL;
}

// Destructor
template < class DT >
List<DT>::~List()
{
	clear();
	delete head;
	delete cursor;
}


//------------ List manipulation operations ------------------

// Insert after cursor
template < class DT >
void List<DT>::insert(const DT& newDataItem)
{
	if (isFull() == true)	//���� á�� �� ����ó��
	{
		cout << "List is Full" << endl;
	}
	else if (head == NULL)	//������� �� �ֱ�
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, NULL, NULL);
		newNode->dataItem = newDataItem;

		head = newNode;
		cursor = newNode;
	}
	else if (head != NULL && cursor->next == NULL) 	//����Ʈ ���� �ֱ�
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, NULL, NULL);
		newNode->dataItem = newDataItem;

		cursor->next = newNode;
		newNode->prior = cursor;
		cursor = newNode;
	}
	else	//����Ʈ�� �߰��� �ֱ�
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, NULL, NULL);
		newNode->dataItem = newDataItem;

		newNode->next = cursor->next;
		newNode->prior = cursor;
		cursor->next->prior = newNode;
		cursor->next = newNode;
		cursor = newNode;
	}

}

// Remove data item
template < class DT >
void List<DT>::remove()
{
	ListNode<DT>* tempPtr;

	if (isEmpty() == true)		//����Ʈ ����� �� ����ó��
	{
		cout << "List is Empty" << endl;
	}
	else if (cursor->next == NULL && cursor->prior == NULL)		//����Ʈ�� ��� �ϳ��� ��
	{
		delete head;
		head = NULL;
		cursor = NULL;
	}
	else if (cursor->next == NULL && cursor->prior != NULL)		//Ŀ���� ����Ʈ �� ���� ��(Ŀ�� �Ǿ�����)
	{
		tempPtr = cursor->prior;	//tempPtr�� ���� ����� ���� ��带 ����Ŵ
		cursor = head;				//cursor�� ����Ʈ �� ���̹Ƿ� head��
		delete tempPtr->next;		
		tempPtr->next = NULL;		
	}
	else if (cursor == head && cursor->next != NULL)		//Ŀ���� ����Ʈ �� ���̰�, ��尡 �������� ���� ��
	{
		cursor = cursor->next;
		delete cursor->prior;
		cursor->prior = NULL;
		head = cursor;
	}
	else		//Ŀ���� ����Ʈ �߰��� ���� ��
	{
		tempPtr = cursor;			//tempPtr�� ���� ��带 ����Ŵ
		cursor = tempPtr->next;		//cursor�� ���� ����
		tempPtr->prior->next = cursor;
		cursor->prior = tempPtr->prior;
		delete tempPtr;
	}
}

// Replace data item
template < class DT >
void List<DT>::replace(const DT& newElement)
{
	if (isEmpty() == true)			//List ����� �� ����ó��
	{
		cout << "List is Empty" << endl;
	}
	else
	{
		cursor->dataItem = newElement;
	}
}

// Clear list
template < class DT >
void List<DT>::clear()
{
	ListNode<DT>* tempPtr = head;

	while (tempPtr != NULL)		//head���� �Ҵ� ����
	{
		head = head->next;
		delete tempPtr;
		tempPtr = head;
	}

	head = NULL;
	cursor = NULL;
}


//------------ List status operations ------------------

// List is empty
template < class DT >
bool List<DT>::isEmpty() const
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// List is full
template < class DT >
bool List<DT>::isFull() const
{
	ListNode<DT>* testNode = new ListNode<DT>(0, NULL, NULL);

	if (testNode == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//------------ List manipulation operations ------------------

// Go to beginning
template < class DT >
void List<DT>::gotoBeginning()
{
	if (isEmpty() == true)			//List ����� �� ����ó��
	{
		cout << "List is Empty" << endl;
	}
	else
	{
		cursor = head;
	}
}

// Go to end
template < class DT >
void List<DT>::gotoEnd()
{
	if (isEmpty() == true)			//List ����� �� ����ó��
	{
		cout << "List is Empty" << endl;
	}
	else
	{
		while (cursor->next != NULL)	//cursor�� List�� ������ ����
		{
			cursor = cursor->next;
		}
	}
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
	if (isEmpty() == true)			//List ����� �� ����ó��
	{
		cout << "List is Empty" << endl;
		return false;
	}
	else if (cursor->next == NULL)
	{
		cout << "cursor is pointing end of the list" << endl;
		return false;
	}
	else
	{
		cursor = cursor->next;
		return true;
	}
}

// Go to prior data item
template < class DT >
bool List<DT>::gotoPrior()
{
	if (isEmpty() == true)			//List ����� �� ����ó��
	{
		cout << "List is Empty" << endl;
		return false;
	}
	else if (cursor == head)		//Ŀ���� List�� �� ���� �� ����ó��
	{
		cout << "cursor is pointing beginning of the list" << endl;
		return false;
	}
	else
	{
		cursor = cursor->prior;
		return true;
	}
}


template < class DT >
DT List<DT>::getCursor() const
{
	if (isEmpty() == true)
	{
		cout << "List is Empty" << endl;
		return 0;
	}
	else
	{
		return cursor->dataItem;
	}
}


//-----------------------------------------------------------

template < class DT >
void List<DT>::showStructure() const
{
	if (isEmpty() == true)
	{
		cout << "Empty List" << endl;
	}
	else
	{
		ListNode<DT>* showPtr = head;

		while (showPtr != NULL)
		{
			if (showPtr == cursor)
			{
				cout << "[" << showPtr->dataItem << "] ";
			}
			else
			{
				cout << showPtr->dataItem << " ";
			}

			showPtr = showPtr->next;
		}

		cout << endl;
	}
}