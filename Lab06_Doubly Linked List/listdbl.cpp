
#include <iostream>
#include "listdbl.h"

using namespace std;

//ListNode의 Constructor
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
	if (isFull() == true)	//가득 찼을 때 예외처리
	{
		cout << "List is Full" << endl;
	}
	else if (head == NULL)	//비어있을 때 넣기
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, NULL, NULL);
		newNode->dataItem = newDataItem;

		head = newNode;
		cursor = newNode;
	}
	else if (head != NULL && cursor->next == NULL) 	//리스트 끝에 넣기
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, NULL, NULL);
		newNode->dataItem = newDataItem;

		cursor->next = newNode;
		newNode->prior = cursor;
		cursor = newNode;
	}
	else	//리스트의 중간에 넣기
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

	if (isEmpty() == true)		//리스트 비었을 때 예외처리
	{
		cout << "List is Empty" << endl;
	}
	else if (cursor->next == NULL && cursor->prior == NULL)		//리스트에 노드 하나일 때
	{
		delete head;
		head = NULL;
		cursor = NULL;
	}
	else if (cursor->next == NULL && cursor->prior != NULL)		//커서가 리스트 맨 끝일 때(커서 맨앞으로)
	{
		tempPtr = cursor->prior;	//tempPtr은 지울 노드의 이전 노드를 가리킴
		cursor = head;				//cursor가 리스트 맨 끝이므로 head로
		delete tempPtr->next;		
		tempPtr->next = NULL;		
	}
	else if (cursor == head && cursor->next != NULL)		//커서가 리스트 맨 앞이고, 노드가 유일하지 않을 때
	{
		cursor = cursor->next;
		delete cursor->prior;
		cursor->prior = NULL;
		head = cursor;
	}
	else		//커서가 리스트 중간에 있을 때
	{
		tempPtr = cursor;			//tempPtr은 지울 노드를 가리킴
		cursor = tempPtr->next;		//cursor는 다음 노드로
		tempPtr->prior->next = cursor;
		cursor->prior = tempPtr->prior;
		delete tempPtr;
	}
}

// Replace data item
template < class DT >
void List<DT>::replace(const DT& newElement)
{
	if (isEmpty() == true)			//List 비었을 때 예외처리
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

	while (tempPtr != NULL)		//head부터 할당 해제
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
	if (isEmpty() == true)			//List 비었을 때 예외처리
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
	if (isEmpty() == true)			//List 비었을 때 예외처리
	{
		cout << "List is Empty" << endl;
	}
	else
	{
		while (cursor->next != NULL)	//cursor를 List의 마지막 노드로
		{
			cursor = cursor->next;
		}
	}
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
	if (isEmpty() == true)			//List 비었을 때 예외처리
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
	if (isEmpty() == true)			//List 비었을 때 예외처리
	{
		cout << "List is Empty" << endl;
		return false;
	}
	else if (cursor == head)		//커서가 List의 맨 앞일 때 예외처리
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