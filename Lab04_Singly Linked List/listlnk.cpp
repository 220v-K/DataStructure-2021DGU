

#include "listlnk.h"
#include <iostream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
    this->dataItem = nodeData;
    this->next = NULL;
}


template<class DT>
List<DT>::List(int ignored)
{
    head = NULL;
    cursor = NULL;
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
    delete head;
    delete cursor;
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
    if (isFull() == true)                   //List 가득 찼을 때 예외 처리
    {
        cout << "List is Full" << endl;
    }
    else if (head == NULL)                  //List 비었을 때
    {
        ListNode<char>* newNode = new ListNode<char>('\0', NULL);
        newNode->dataItem = newData;
        cursor = newNode;
        head = newNode;
    }
    else
    {                                       //List에 무언가 차 있을 때
        ListNode<char>* newNode = new ListNode<char>('\0', NULL);
        newNode->dataItem = newData;
        cursor->next = newNode;
        cursor = newNode;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
    if (isEmpty() == true)                  //List 비었을 때 예외처리
    {
        cout << "List is Empty" << endl;
    }
    else if (cursor->next == NULL)          //커서가 마지막 item일 때
    {
        ListNode<char>* prevPtr;
        prevPtr = head;

        if (cursor == head)                 //커서가 List의 마지막 item이고, 유일한 item일 때
        {
            delete cursor;
            cursor = NULL;
            head = NULL;
        }
        else
        {
            while (prevPtr->next != cursor) 
            {
                prevPtr = prevPtr->next;
            }
            cursor = head;
            delete prevPtr->next;
            prevPtr->next = NULL;
        }
    }
    else                                    //커서가 List의 마지막 item이 아닐 때
    {                                       
        if (cursor == head)                 //커서가 head에 있을 때
        {
            cursor = cursor->next;
            delete head;
            head = cursor;
        }
        else                                //아닐 때
        {
            ListNode<char>* prevPtr;
            prevPtr = head;

            while (prevPtr->next != cursor)
            {
                prevPtr = prevPtr->next;
            }
            cursor = cursor->next;
            delete prevPtr->next;
            prevPtr->next = cursor;
        }
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
    if (isEmpty() == true)                  //List 비었을 때 예외처리
    {
        cout << "List is Empty" << endl;
    }
    else
    {
        cursor->dataItem = newData;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
    ListNode<char>* tempPtr = head;

    while (tempPtr != NULL)             //head부터 하나하나 지워나감
    {
        head = tempPtr->next;
        delete tempPtr;
        tempPtr = head;
    }
    head = NULL;                        //마지막엔 head, cursor 모두 NULL로
    cursor = NULL;
}

//------------------------------------------------


template<class DT>
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

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
    ListNode<char>* testNode = new ListNode<char>('\0', NULL); 
    
    if (testNode == NULL)       //새로 노드를 생성해 보고 생성되지 않으면 Full.
    {
        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
    if (isEmpty() == true)              //List가 비어 있을 때 예외처리.
    {
        cout << "List is Empty" << endl;
    }
    else
    {
        cursor = head;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
    if (isEmpty() == true)              //List가 비어 있을 때 예외처리.
    {
        cout << "List is Empty" << endl;
    }
    else
    {
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
        }
    }
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext()
{
    if (isEmpty() == true)              //List가 비어 있을 때 예외처리
    {
        cout << "List is Empty" << endl;
        return false;
    }
    else if (cursor->next == NULL)      //커서가 List의 마지막 item일 때
    {
        return false;
    }
    else
    {
        cursor = cursor->next;
        return true;
    }
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
    if (isEmpty() == true)              //List가 비어 있을 때 예외처리
    {
        cout << "List is Empty" << endl;
        return false;
    }
    else if (cursor == head)            //커서가 List의 맨 앞일 때
    {
        return false;
    }
    else
    {
        ListNode<char>* tempPtr = head;
        while (tempPtr->next != cursor)
        {
            tempPtr = tempPtr->next;
        }
        cursor = tempPtr;
        return true;
    }
}

//------------------------------------------------


template<class DT>
DT List<DT>::getCursor() const
{
    if (isEmpty() == true)              //List가 비어 있을 때 예외처리.
    {
        cout << "List is Empty" << endl;
    }
    else
    {
        return cursor->dataItem;
    }
}

template<class DT>
void List<DT>::showStructure() const
{
    if (isEmpty() == true)
    {
        cout << "Empty List" << endl;
    }
    else 
    {
        ListNode<char>* showNode;
        showNode = head;
        while (showNode != NULL)
        {
            if (showNode == cursor)
            {
                cout << "[" << showNode->dataItem << "]";
            }
            else
            {
                cout << showNode->dataItem << " ";
            }
            showNode = showNode->next;
        }
        cout << endl;
    }
}

//------------------------------------------------

//in-lab
template<class DT>
void List<DT>::moveToBeginning()
{
    if (isEmpty() == true)
    {
        cout << "List is Empty" << endl;
    }
    else
    {
        char tempItem;
        tempItem = cursor->dataItem;
        remove();

        ListNode<char>* newNode = new ListNode<char>('\0', NULL);
        newNode->dataItem = tempItem;
        newNode->next = head;
        cursor = newNode;
        head = newNode;
    }
}

template<class DT>
void List<DT>::insertBefore(const DT& newElement)
{
    if (isFull() == true)
    {
        cout << "List is Full" << endl;
    }
    else if (isEmpty() == true)
    {
        insert(newElement);
    }
    else
    {
        char tempItem;
        tempItem = cursor->dataItem;
        ListNode<char>* newNode = new ListNode<char>('\0', NULL);

        newNode->dataItem = tempItem;
        newNode->next = cursor->next;
        cursor->next = newNode;
        cursor->dataItem = newElement;
    }
}