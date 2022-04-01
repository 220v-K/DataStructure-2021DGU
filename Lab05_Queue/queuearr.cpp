
#include "queuearr.h"
#include <iostream>

using namespace std;

template <class DT>
Queue<DT>::Queue(int maxNumber) throw (bad_alloc)

	:maxSize(maxNumber),
	front(maxSize),				//front, rear�� �ʱⰪ. front�� �� ���� ���� �� ĭ ���� point, rear�� �� ���� ���� point��.
	rear(maxSize)
{
	element = new DT[maxSize + 1];		//�迭 ���� �Ҵ� (isEmpty, isFull�� ó���ϱ� ���� maxSize���� ũ�Ⱑ �ϳ� ū �迭�� ����)
	for (int i = 0; i < maxSize + 1; i++)	//�迭 �ʱ�ȭ
	{
		element[i] = 0;
	}
}

template <class DT>
Queue<DT>::~Queue()
{
	delete[] element;			//�Ҵ� ����
}

template <class DT>
void Queue<DT>::enqueue(const DT& newDataItem) throw (logic_error)
{
	if (isFull() == true)		//Queue�� Full�� �� ����ó��
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		rear = (rear + 1) % (maxSize + 1);				//rear�� ���� ĭ�� point��Ű�� �� �ڸ��� ���� ����. (mod������ �̿��� ������ ĭ�̶�� ù ĭ����)
		element[rear] = newDataItem;
	}
}

template <class DT>
DT Queue<DT>::dequeue() throw (logic_error)
{
	DT tempelement;

	if (isEmpty() == true)		//Queue�� Empty�� �� ����ó��
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		front = (front + 1) % (maxSize + 1);		//front�� ���� ĭ�� point ��Ű�� �� �ڸ��� ���� ����. (�׷����ν�, front�� �� ���� ���� 1ĭ ���� point�ϰ� ��.) (mod������ �̿��� ������ ĭ�̶�� ù ĭ����)
		tempelement = element[front];
		element[front] = 0;
		return tempelement;
	}

}

template <class DT>
void Queue<DT>::clear()
{
	for (int i = 0; i < maxSize + 1; i++)	//�迭�� ���� ��� ���ְ�
	{
		element[i] = 0;		
	}
	front = maxSize;		//front, rear�� ��� �ʱⰪ����
	rear = maxSize;
}

template <class DT>
bool Queue<DT>::isEmpty() const
{
	if (rear == front)
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
	if ((rear + 1) % (maxSize + 1) == front)	//rear�� ���� ĭ�� front���� Ȯ��. rear + 1 == front�� front=0 / rear=maxSize�� �� Full�� ��µ��� ������ ����.
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
	int temppoint;

	if (isEmpty() == true)						//Queue�� Empty�� �� ����ó��.
	{
		cout << "Empty Queue" << endl;
	}
	else
	{
		for (int i = 0; i < maxSize + 1; i++)		
		{
			temppoint = (front + 1 + i) % (maxSize + 1);		//temppoint�� �̿��� front ���� ĭ(�� ���� ��) ���� ����� �� �ֵ��� ��.

			if (element[temppoint] == 0 || temppoint == front)
			{
				continue;
			}
			else 
			{
				cout << " [" << element[temppoint] << "] ";
			}
		}
		cout << endl;
	}		
	cout << "maxSize: " << maxSize << "   " << "front: " << front << "   " << "rear: " << rear << endl;	//test�� front�� rear, maxSize Ȯ��
}

template <class DT>
void Queue<DT>::putFront(const DT& newDataItem) throw (logic_error)
{
	if (isFull() == true)					//Queue�� Full�� �� ����ó��.
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		element[front] = newDataItem;		//front ��ġ�� ���� �ְ�
		if (front == 0)						//front�� point�ϴ� ��ġ�� �� ĭ ������ ���. �� ��, front = 0�̶�� front�� �� �ڷ�.
		{
			front = maxSize;
		}
		else
		{
			front = front - 1;
		}
	}
}

template <class DT>
DT Queue<DT>::getRear() throw (logic_error)
{
	DT tempelement;

	if (isEmpty() == true)					//Queue�� Empty�� �� ����ó��.
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		tempelement = element[rear];		//���� �� �ӽ� ����
		element[rear] = 0;					//rear��ġ�� ���� ���ְ�
		if (rear == 0)						//rear�� point�ϴ� ��ġ�� �� ĭ ������ ���. �� ��, rear = 0�̶�� rear�� �� �ڷ�.
		{
			rear = maxSize;
		}
		else
		{
			rear = rear - 1;
		}
		return tempelement;
	}
}

template <class DT>
int Queue<DT> ::getLength() const
{
	if (front == rear)						//front = rear�� Queue�� Empty�̹Ƿ� data item�� ���� 0 ��ȯ.
	{
		return 0;
	}
	else if (front < rear)					//front < rear�� rear-front�� data item�� ����.
	{
		return rear - front;
	}
	else									//front > rear�� [maxSize - (front - rear - 1)]�� date item ����.
	{
		return maxSize - (front - rear - 1);
	}
}