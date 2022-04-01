
//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.cpp
//
//  Actual implementation of class in the Heap ADT
//--------------------------------------------------------------------

#include "heap.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------------


template<class DT>
Heap<DT>::Heap(int maxNumber)
{
    dataItems = new DT[maxNumber];      //maxNumber 크기의 DT(TestDataItem)형 배열 동적 할당.
    DT NULLob;
    NULLob.setPty(0);
    for (int i = 0; i < maxNumber; i++)
    {
        dataItems[i] = NULLob;
    }
    maxSize = maxNumber;
    size = 0;
}

template < class DT >
Heap<DT>::~Heap()
{
    delete[] dataItems;     //할당 해제.
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::insert(const DT& newElement)
{
    if (isFull() == true)       //Full일 때 예외처리
    {
        cout << "Heap is Full" << endl;
    }
    else
    {       
        dataItems[size] = newElement;      //bottom의 Rightmost에 넣음.
        int cursor = size;

        DT tempDT;

        while (cursor != 0)     //ReHeapUp
        {
            if (dataItems[cursor].pty() > dataItems[(cursor - 1) / 2].pty())    //item의 priority가 parent의 priority보다 높다면 서로 위치를 바꿈.
            {
                tempDT = dataItems[cursor];
                dataItems[cursor] = dataItems[(cursor - 1) / 2];
                dataItems[(cursor - 1) / 2] = tempDT;
                cursor = (cursor - 1) / 2;
            }
            else            //item의 priority가 parent의 priority보다 높지 않다면, cursor에 0을 넣어 while문을 끝날 수 있게 함.
                cursor = 0;
        }
        size++;
    }
}

template < class DT >
DT Heap<DT>::removeMax()
{
    if (isEmpty() == true)      //Empty일 때 예외처리
    {
        cout << "Heap is Empty" << endl;
        DT test;
        test.setPty(-1);
        return test;
    }
    else
    {
        DT temp = dataItems[0];     //root의 DT return을 위해 temp에 저장.
        DT NULLob;
        NULLob.setPty(0);

        size--;     //size를 미리 줄임.
        dataItems[0] = dataItems[size];     //root에 rightmost를 넣음. / 1 줄인 size는 원래의 rightmost의 index.
        dataItems[size] = NULLob;

        int cursor = 0;
        int left = cursor * 2 + 1;      //가독성 좋게 left와 right childnode의 index.
        int right = cursor * 2 + 2;

        //left 자식 노드가 없다면, 이미 leaf에 도달한 것.
        while (dataItems[left].pty() != 0)    //ReHeapDown
        {
            //left 자식 노드만 존재할 때
            if (dataItems[right].pty() == 0)
            {
                if (dataItems[left].pty() >= dataItems[cursor].pty())    //left 자식 노드의 priority가 더 높다면
                {
                    DT tempDT = dataItems[cursor];          //서로 바꿔줌
                    dataItems[cursor] = dataItems[left];
                    dataItems[left] = tempDT;
                    cursor = left;      //커서는 바꿔준 left자식노드로
                }
                else        //아니라면 while문 밖으로 탈출
                    break;
            }
            //left, right 둘 다 존재할 때
            else
            {
                if (dataItems[left].pty() > dataItems[right].pty())         // left > right
                {
                    if (dataItems[left].pty() >= dataItems[cursor].pty())    // left > right, left >= cursor
                    {
                        DT tempDT = dataItems[cursor];          //서로 바꿔줌
                        dataItems[cursor] = dataItems[left];
                        dataItems[left] = tempDT;
                        cursor = left;      //커서는 바꿔준 left자식노드로
                    }
                    else
                        break;
                }
                else        // right >= left
                {
                    if (dataItems[right].pty() >= dataItems[cursor].pty())    // right >= left, right >= cursor
                    {
                        DT tempDT = dataItems[cursor];          //서로 바꿔줌
                        dataItems[cursor] = dataItems[right];
                        dataItems[right] = tempDT;
                        cursor = right;      //커서는 바꿔준 right자식노드로
                    }
                    else
                        break;
                }
            }
            left = cursor * 2 + 1;
            right = cursor * 2 + 2;
        }

        return temp;    //root의 DT return.
    }
}

template < class DT >
void Heap<DT>::clear()   //maxSize 이용해서 다시.
{
    delete[] dataItems;
    dataItems = new DT[maxSize];
    DT NULLob;
    NULLob.setPty(0);
    for (int i = 0; i < maxSize; i++)
    {
        dataItems[i] = NULLob;
    }
    size = 0;
}

//--------------------------------------------------------------------

template < class DT >
bool Heap<DT>::isEmpty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

template < class DT >
bool Heap<DT>::isFull() const
{
    if (size == maxSize)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

template < class HD >
void Heap<HD>::showStructure() const

// Outputs the priorities of the data in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if (size == 0)
        cout << "Empty heap" << endl;
    else
    {
        cout << "size = " << size << endl;       // Output array form
        for (j = 0; j < maxSize; j++)
            cout << j << "\t";
        cout << endl;
        for (j = 0; j < size; j++)
            cout << dataItems[j].pty() << "\t";
        cout << endl << endl;
        showSubtree(0, 0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void Heap<DT>::showSubtree(int index, int level) const

// Recursive partner of the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
    int j;   // Loop counter

    if (index < size)
    {
        showSubtree(2 * index + 2, level + 1);        // Output right subtree
        for (j = 0; j < level; j++)        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].pty();   // Output dataItems's pty
        if (2 * index + 2 < size)                // Output "connector"
            cout << "<";
        else if (2 * index + 1 < size)
            cout << "\\";
        cout << endl;
        showSubtree(2 * index + 1, level + 1);        // Output left subtree
    }
}