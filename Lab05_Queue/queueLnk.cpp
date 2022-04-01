
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
	front = NULL;		//front, rear �������� �ʱⰪ.
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
	if (isFull() == true)		//Queue�� Full�� �� ����ó��
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		if (isEmpty() == true)		//Queue�� ����� ��
		{
			QueueNode<DT>* newNode = new QueueNode<DT>('\0', NULL);	//�� ��� ����
			newNode->dataItem = newDataItem;						//�� ����� dataItem �Է�
			front = newNode;										//front�� rear ��� �� ��带 point
			rear = newNode;
		}
		else					//Queue�� ������� ���� ��
		{
			QueueNode<DT>* newNode = new QueueNode<DT>('\0', NULL);	//�� ��� ����
			newNode->dataItem = newDataItem;						//�� ����� dataItem �Է�
			rear->next = newNode;									//���� rear�� point�ϴ� ��尡 �� ��带 point
			rear = newNode;											//rear�� �� ��带 point
		}
	}
}

template <class DT>
DT Queue<DT>::dequeue()
{
	DT tempelement;

	if (isEmpty() == true)		//Queue�� Empty�� �� ����ó��
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		if (front->next == NULL)		//Queue�� ��尡 1�� ���� ��
		{
			tempelement = front->dataItem;
			delete front;												//�ϳ����� ��带 �����ϸ� ��
			front = NULL;
			rear = NULL;
		}
		else
		{
			tempelement = front->dataItem;
			QueueNode<DT>* tempPtr;										//��� ������ ���� tempPtr ������ ����
			tempPtr = front;
			front = front->next;										//front�� ���� ��带 point�ϰ� �ٲٰ�
			delete tempPtr;												//���� front�� point�ϴ� ���(tempPtr�� point�ϴ� ���) ����.
		}
	}

	return tempelement;
}

template <class DT>
void Queue<DT>::clear()
{
	QueueNode<DT>* tempPtr = front;		//��� ������ ������

	while (tempPtr != NULL)             //front���� �ϳ��� ����
	{
		front = front->next;
		delete tempPtr;
		tempPtr = front;
	}
	front = NULL;                        //front, rear ��� NULL�� �ʱ�ȭ
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
	QueueNode<DT>* testNode = new QueueNode<DT>('\0', NULL);		//���ο� ��带 ������ ��

	if (testNode == NULL)											//�� ��尡 �������� ������ Full.	
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
		QueueNode<DT>* showNode;		//��¿� �ӽ� ���
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
	if (isFull() == true)					//Queue�� Full�� �� ����ó��.
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		if (isEmpty() == true)					//Queue�� ������� ��, rear���� �������� �Ǵϱ�~
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

	if (isEmpty() == true)						//Queue�� Empty�� �� ����ó��.
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		if (front->next == NULL)				//Queue�� ��尡 1�� ���� ��
		{
			tempelement = front->dataItem;
			delete front;						//�ϳ����� ��带 �����ϸ� ��
			front = NULL;
			rear = NULL;
		}
		else
		{
			tempelement = rear->dataItem;		//���� �� �ӽ� ����

			QueueNode<DT>* tempPtr = front;
			while (tempPtr->next != rear)		//tempPtr�� ����, rear�� �ٷ� �� ��带 point.
			{
				tempPtr = tempPtr->next;
			}
			tempPtr->next = NULL;
			delete rear;						//rear�� point�ϴ� ��� ����
			rear = tempPtr;						//rear�� �ٽ� �� �������� ���(tempPtr�� point�ϴ�)�� point.			
		}
	}

	return tempelement;
}

template <class DT>
int Queue<DT> ::getLength() const
{
	int num_Node = 0;							//��� �� ����� ����

	QueueNode<DT>* tempPtr = front;
	while (tempPtr != NULL)					//front���� �����鼭 num_Node�� ������Ŵ
	{
		num_Node = num_Node + 1;
		tempPtr = tempPtr->next;
	}

	return num_Node;
}