
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
    dataItems = new DT[maxNumber];      //maxNumber ũ���� DT(TestDataItem)�� �迭 ���� �Ҵ�.
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
    delete[] dataItems;     //�Ҵ� ����.
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::insert(const DT& newElement)
{
    if (isFull() == true)       //Full�� �� ����ó��
    {
        cout << "Heap is Full" << endl;
    }
    else
    {       
        dataItems[size] = newElement;      //bottom�� Rightmost�� ����.
        int cursor = size;

        DT tempDT;

        while (cursor != 0)     //ReHeapUp
        {
            if (dataItems[cursor].pty() > dataItems[(cursor - 1) / 2].pty())    //item�� priority�� parent�� priority���� ���ٸ� ���� ��ġ�� �ٲ�.
            {
                tempDT = dataItems[cursor];
                dataItems[cursor] = dataItems[(cursor - 1) / 2];
                dataItems[(cursor - 1) / 2] = tempDT;
                cursor = (cursor - 1) / 2;
            }
            else            //item�� priority�� parent�� priority���� ���� �ʴٸ�, cursor�� 0�� �־� while���� ���� �� �ְ� ��.
                cursor = 0;
        }
        size++;
    }
}

template < class DT >
DT Heap<DT>::removeMax()
{
    if (isEmpty() == true)      //Empty�� �� ����ó��
    {
        cout << "Heap is Empty" << endl;
        DT test;
        test.setPty(-1);
        return test;
    }
    else
    {
        DT temp = dataItems[0];     //root�� DT return�� ���� temp�� ����.
        DT NULLob;
        NULLob.setPty(0);

        size--;     //size�� �̸� ����.
        dataItems[0] = dataItems[size];     //root�� rightmost�� ����. / 1 ���� size�� ������ rightmost�� index.
        dataItems[size] = NULLob;

        int cursor = 0;
        int left = cursor * 2 + 1;      //������ ���� left�� right childnode�� index.
        int right = cursor * 2 + 2;

        //left �ڽ� ��尡 ���ٸ�, �̹� leaf�� ������ ��.
        while (dataItems[left].pty() != 0)    //ReHeapDown
        {
            //left �ڽ� ��常 ������ ��
            if (dataItems[right].pty() == 0)
            {
                if (dataItems[left].pty() >= dataItems[cursor].pty())    //left �ڽ� ����� priority�� �� ���ٸ�
                {
                    DT tempDT = dataItems[cursor];          //���� �ٲ���
                    dataItems[cursor] = dataItems[left];
                    dataItems[left] = tempDT;
                    cursor = left;      //Ŀ���� �ٲ��� left�ڽĳ���
                }
                else        //�ƴ϶�� while�� ������ Ż��
                    break;
            }
            //left, right �� �� ������ ��
            else
            {
                if (dataItems[left].pty() > dataItems[right].pty())         // left > right
                {
                    if (dataItems[left].pty() >= dataItems[cursor].pty())    // left > right, left >= cursor
                    {
                        DT tempDT = dataItems[cursor];          //���� �ٲ���
                        dataItems[cursor] = dataItems[left];
                        dataItems[left] = tempDT;
                        cursor = left;      //Ŀ���� �ٲ��� left�ڽĳ���
                    }
                    else
                        break;
                }
                else        // right >= left
                {
                    if (dataItems[right].pty() >= dataItems[cursor].pty())    // right >= left, right >= cursor
                    {
                        DT tempDT = dataItems[cursor];          //���� �ٲ���
                        dataItems[cursor] = dataItems[right];
                        dataItems[right] = tempDT;
                        cursor = right;      //Ŀ���� �ٲ��� right�ڽĳ���
                    }
                    else
                        break;
                }
            }
            left = cursor * 2 + 1;
            right = cursor * 2 + 2;
        }

        return temp;    //root�� DT return.
    }
}

template < class DT >
void Heap<DT>::clear()   //maxSize �̿��ؼ� �ٽ�.
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