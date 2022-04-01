
#include "queuearr.h"
#include <iostream>

using namespace std;

template <class DT>
Queue<DT>::Queue(int maxNumber) throw (bad_alloc)

	:maxSize(maxNumber),
	front(maxSize),				//front, rear의 초기값. front는 맨 앞의 값의 한 칸 앞을 point, rear는 맨 뒤의 값을 point함.
	rear(maxSize)
{
	element = new DT[maxSize + 1];		//배열 동적 할당 (isEmpty, isFull을 처리하기 위해 maxSize보다 크기가 하나 큰 배열을 생성)
	for (int i = 0; i < maxSize + 1; i++)	//배열 초기화
	{
		element[i] = 0;
	}
}

template <class DT>
Queue<DT>::~Queue()
{
	delete[] element;			//할당 해제
}

template <class DT>
void Queue<DT>::enqueue(const DT& newDataItem) throw (logic_error)
{
	if (isFull() == true)		//Queue가 Full일 때 예외처리
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		rear = (rear + 1) % (maxSize + 1);				//rear를 다음 칸을 point시키고 그 자리에 값을 넣음. (mod연산을 이용해 마지막 칸이라면 첫 칸으로)
		element[rear] = newDataItem;
	}
}

template <class DT>
DT Queue<DT>::dequeue() throw (logic_error)
{
	DT tempelement;

	if (isEmpty() == true)		//Queue가 Empty일 때 예외처리
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		front = (front + 1) % (maxSize + 1);		//front를 다음 칸을 point 시키고 그 자리의 값을 없앰. (그럼으로써, front가 맨 앞의 값의 1칸 앞을 point하게 됨.) (mod연산을 이용해 마지막 칸이라면 첫 칸으로)
		tempelement = element[front];
		element[front] = 0;
		return tempelement;
	}

}

template <class DT>
void Queue<DT>::clear()
{
	for (int i = 0; i < maxSize + 1; i++)	//배열의 값을 모두 없애고
	{
		element[i] = 0;		
	}
	front = maxSize;		//front, rear를 모두 초기값으로
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
	if ((rear + 1) % (maxSize + 1) == front)	//rear의 다음 칸이 front인지 확인. rear + 1 == front면 front=0 / rear=maxSize일 때 Full이 출력되지 않음에 유의.
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

	if (isEmpty() == true)						//Queue가 Empty일 때 예외처리.
	{
		cout << "Empty Queue" << endl;
	}
	else
	{
		for (int i = 0; i < maxSize + 1; i++)		
		{
			temppoint = (front + 1 + i) % (maxSize + 1);		//temppoint를 이용해 front 다음 칸(맨 앞의 값) 부터 출력할 수 있도록 함.

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
	cout << "maxSize: " << maxSize << "   " << "front: " << front << "   " << "rear: " << rear << endl;	//test용 front와 rear, maxSize 확인
}

template <class DT>
void Queue<DT>::putFront(const DT& newDataItem) throw (logic_error)
{
	if (isFull() == true)					//Queue가 Full일 때 예외처리.
	{
		cout << "Queue is Full" << endl;
	}
	else
	{
		element[front] = newDataItem;		//front 위치에 값을 넣고
		if (front == 0)						//front가 point하는 위치를 한 칸 앞으로 당김. 이 때, front = 0이라면 front를 맨 뒤로.
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

	if (isEmpty() == true)					//Queue가 Empty일 때 예외처리.
	{
		cout << "Queue is Empty" << endl;
	}
	else
	{
		tempelement = element[rear];		//지울 값 임시 저장
		element[rear] = 0;					//rear위치의 값을 없애고
		if (rear == 0)						//rear가 point하는 위치를 한 칸 앞으로 당김. 이 때, rear = 0이라면 rear를 맨 뒤로.
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
	if (front == rear)						//front = rear면 Queue가 Empty이므로 data item의 개수 0 반환.
	{
		return 0;
	}
	else if (front < rear)					//front < rear면 rear-front가 data item의 개수.
	{
		return rear - front;
	}
	else									//front > rear면 [maxSize - (front - rear - 1)]이 date item 개수.
	{
		return maxSize - (front - rear - 1);
	}
}