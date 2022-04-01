
#include "queueLnk.h"
#include <iostream>

using namespace std;

template <class DT>
QueueNode<DT>::QueueNode(const DT& nodeData, QueueNode* nextPtr)	//Node Constructor.
{
	this->dataItem = nodeData;
	this->next = NULL;
}


template <class DT>
Queue<DT>::Queue(int maxNumber)
{
	front = NULL;		//front, rear 포인터의 초기값.
	rear = NULL;
}

template <class DT>
Queue<DT>::~Queue()
{
	delete front;	
	delete rear;
}

template <class DT>
void Queue<DT>::enqueue(const DT& newDataItem)
{
	if (isFull() == true)		//Queue가 Full일 때 예외처리
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		if (isEmpty() == true)		//Queue가 비었을 때
		{
			QueueNode<DT>* newNode = new QueueNode<DT>('\0', NULL);	//새 노드 생성
			newNode->dataItem = newDataItem;						//새 노드의 dataItem 입력
			front = newNode;										//front와 rear 모두 새 노드를 point
			rear = newNode;
		}
		else					//Queue가 비어있지 않을 때
		{
			QueueNode<DT>* newNode = new QueueNode<DT>('\0', NULL);	//새 노드 생성
			newNode->dataItem = newDataItem;						//새 노드의 dataItem 입력
			rear->next = newNode;									//원래 rear가 point하던 노드가 새 노드를 point
			rear = newNode;											//rear가 새 노드를 point
		}
	}
}

template <class DT>
DT Queue<DT>::dequeue()
{
	DT tempelement;

	if (isEmpty() == true)		//Queue가 Empty일 때 예외처리
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		if (front->next == NULL)		//Queue에 노드가 1개 뿐일 때
		{
			tempelement = front->dataItem;
			delete front;												//하나뿐인 노드를 삭제하면 끝
			front = NULL;
			rear = NULL;
		}
		else
		{
			tempelement = front->dataItem;
			QueueNode<DT>* tempPtr;										//노드 삭제를 위한 tempPtr 포인터 생성
			tempPtr = front;
			front = front->next;										//front를 다음 노드를 point하게 바꾸고
			delete tempPtr;												//원래 front가 point하던 노드(tempPtr이 point하는 노드) 삭제.
		}
	}

	return tempelement;
}

template <class DT>
void Queue<DT>::clear()
{
	QueueNode<DT>* tempPtr = front;		//노드 삭제용 포인터

	while (tempPtr != NULL)             //front부터 하나씩 삭제
	{
		front = front->next;
		delete tempPtr;
		tempPtr = front;
	}
	front = NULL;                        //front, rear 모두 NULL로 초기화
	rear = NULL;
}

template <class DT>
bool Queue<DT>::isEmpty() const
{
	if (front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class DT>
bool Queue<DT>::isFull() const
{
	QueueNode<DT>* testNode = new QueueNode<DT>('\0', NULL);		//새로운 노드를 생성해 봄

	if (testNode == NULL)											//그 노드가 생성되지 않으면 Full.	
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class DT>
void Queue<DT>::showStructure() const
{
	if (isEmpty() == true)
	{
		cout << "Empty List" << endl;
	}
	else
	{
		QueueNode<DT>* showNode;		//출력용 임시 노드
		showNode = front;
		while (showNode != NULL)
		{
			cout << " [" << showNode->dataItem << "] ";
			showNode = showNode->next;
		}
		cout << endl;
	}
}

template <class DT>
void Queue<DT>::putFront(const DT& newDataItem)
{
	if (isFull() == true)					//Queue가 Full일 때 예외처리.
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		if (isEmpty() == true)					//Queue가 비어있을 때, rear값도 만들어줘야 되니까~
		{
			QueueNode<DT>* newNode = new QueueNode<DT>('\0', NULL);
			newNode->dataItem = newDataItem;
			newNode->next = front;
			front = newNode;
			rear = newNode;
		}
		else
		{
			QueueNode<DT>* newNode = new QueueNode<DT>('\0', NULL);
			newNode->dataItem = newDataItem;
			newNode->next = front;
			front = newNode;
		}
	}
}

template <class DT>
DT Queue<DT>::getRear()
{
	DT tempelement;

	if (isEmpty() == true)						//Queue가 Empty일 때 예외처리.
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		if (front->next == NULL)				//Queue에 노드가 1개 뿐일 때
		{
			tempelement = front->dataItem;
			delete front;						//하나뿐인 노드를 삭제하면 끝
			front = NULL;
			rear = NULL;
		}
		else
		{
			tempelement = rear->dataItem;		//지울 값 임시 저장

			QueueNode<DT>* tempPtr = front;
			while (tempPtr->next != rear)		//tempPtr을 생성, rear의 바로 전 노드를 point.
			{
				tempPtr = tempPtr->next;
			}
			tempPtr->next = NULL;
			delete rear;						//rear가 point하던 노드 삭제
			rear = tempPtr;						//rear가 다시 맨 마지막의 노드(tempPtr이 point하는)를 point.			
		}
	}

	return tempelement;
}

template <class DT>
int Queue<DT> ::getLength() const
{
	int num_Node = 0;							//노드 수 저장용 변수

	QueueNode<DT>* tempPtr = front;
	while (tempPtr != NULL)					//front부터 훑으면서 num_Node를 증가시킴
	{
		num_Node = num_Node + 1;
		tempPtr = tempPtr->next;
	}

	return num_Node;
}