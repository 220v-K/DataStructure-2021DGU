
//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
//
//--------------------------------------------------------------------
#include "stackarr.h"

//--------------------------------------------------------------------

template <class DT>
Stack<DT>::Stack(int maxNumber)		//maxNumber = 8

	: maxSize(maxNumber),
	top(-1)
{
	element = new DT[maxNumber];	//배열 할당
	for (int i = 0; i < maxSize; i++)
	{
		element[i] = 0;
	}
}

//--------------------------------------------------------------------

template <class DT>
Stack<DT>:: ~Stack()
{
	delete[] element;	//할당 해제
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::push(const DT& newElement)
{
	if (isFull())
	{
		cout << "Can't push : Stack is Full" << endl;
	}
	else
	{
		top++;
		element[top] = newElement;
	}
}

//--------------------------------------------------------------------

template <class DT>
DT Stack<DT>::pop()
{
	DT temp_element;

	if (isEmpty())
	{
		cout << "Can't pop : Stack is Empty" << endl;
	}
	else
	{
		temp_element = element[top];
		element[top] = 0;
		top--;
		return temp_element;
	}

}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::clear()		//Stack 내 데이터 삭제
{
	top = -1;

	for (int i = 0; i < maxSize; i++)
	{
		element[i] = 0;
	}

}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const		//Stack이 비어 있을 때 true, 아니면 false 반환
{
	if (top == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isFull() const		//Stack이 꽉 차 있을 때 true, 아니면 false 반환
{
	if (top + 1 == maxSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::showStructure() const
{
	if (top == -1)		//Stack이 비어 있으면
	{
		cout << "Empty Stack" << endl;
	}
	else
	{
		for (int i = 0; i < maxSize; i++)
		{
			if (element[i] == 0)
			{
				cout << "[ Empty ] ";		//Stack 내 빈 칸
			}
			else
			{
				cout << "[ " << element[i] << " ] ";		//Stack 내 element가 존재하는 칸
			}
		}
		cout << endl;
	}
}
