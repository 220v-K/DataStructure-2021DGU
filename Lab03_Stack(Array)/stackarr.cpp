
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
	element = new DT[maxNumber];	//�迭 �Ҵ�
	for (int i = 0; i < maxSize; i++)
	{
		element[i] = 0;
	}
}

//--------------------------------------------------------------------

template <class DT>
Stack<DT>:: ~Stack()
{
	delete[] element;	//�Ҵ� ����
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
void Stack<DT>::clear()		//Stack �� ������ ����
{
	top = -1;

	for (int i = 0; i < maxSize; i++)
	{
		element[i] = 0;
	}

}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const		//Stack�� ��� ���� �� true, �ƴϸ� false ��ȯ
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
bool Stack<DT>::isFull() const		//Stack�� �� �� ���� �� true, �ƴϸ� false ��ȯ
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
	if (top == -1)		//Stack�� ��� ������
	{
		cout << "Empty Stack" << endl;
	}
	else
	{
		for (int i = 0; i < maxSize; i++)
		{
			if (element[i] == 0)
			{
				cout << "[ Empty ] ";		//Stack �� �� ĭ
			}
			else
			{
				cout << "[ " << element[i] << " ] ";		//Stack �� element�� �����ϴ� ĭ
			}
		}
		cout << endl;
	}
}
