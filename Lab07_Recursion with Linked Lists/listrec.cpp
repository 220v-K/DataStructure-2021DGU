
//--------------------------------------------------------------------
//
//  Laboratory 10                                         listrec.cs
//
//  (Shell) Partial linked list implementation of the List ADT with
//  additional recursive linked list functions
//
//--------------------------------------------------------------------

#include <iostream>
#include "listrec.h"

using namespace std;

//--------------------------------------------------------------------
//
// Insert your singly linked list implementations (from Laboratory 7)
// of the following functions:
//
//   - The ListNode class constructor
//
//   - The List class constructor, destructor, insert(), clear(), and
//     showstructure() functions. You may also need to add empty()
//     full(), and others.
//
//--------------------------------------------------------------------

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
    this->dataItem = nodeData;
    this->next = nextPtr;
}

template<class DT>
List<DT>::List(int ignored)
{
    head = NULL;
    cursor = NULL;
}

template<class DT>
List<DT>::~List()
{
    delete head;
    delete cursor;
}

//--------------------------------------------------------------------

template<class DT>
void List<DT>::insert(const DT& newData)
{
    //if (isFull() == true)                   //List 가득 찼을 때 예외 처리
    //{
    //    cout << "List is Full" << endl;
    //}
    if (head == NULL)                  //List 비었을 때
    {
        ListNode<DT>* newNode = new ListNode<DT>('\0', NULL);
        newNode->dataItem = newData;
        cursor = newNode;
        head = newNode;
    }
    else
    {                                       //List에 무언가 차 있을 때
        ListNode<DT>* newNode = new ListNode<DT>('\0', NULL);
        newNode->dataItem = newData;
        cursor->next = newNode;
        cursor = newNode;
    }
}

template<class DT>
void List<DT>::clear()
{
    ListNode<DT>* tempPtr = head;

    while (tempPtr != NULL)             //head부터 하나하나 지워나감
    {
        head = tempPtr->next;
        delete tempPtr;
        tempPtr = head;
    }
    head = NULL;                        //마지막엔 head, cursor 모두 NULL로
    cursor = NULL;
}

template<class DT>
void List<DT>::showStructure() const
{
    if (head == NULL)
    {
        cout << "Empty List" << endl;
    }
    else
    {
        ListNode<DT>* showNode;
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


//--------------------------------------------------------------------
//
// Recursively implemented linked list functions used in the Prelab
// Exercise
//
//--------------------------------------------------------------------

template < class DT >
void List<DT>::write() const

// Outputs the data in a list from beginning to end. Assumes that
// objects of type DT can be output to the cout stream.

{
    cout << "List : ";
    writeSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::writeSub(ListNode<DT>* p) const

// Recursive partner of the write() function. Processes the sublist
// that begins with the node pointed to by p.

{
    if (p != 0)
    {
        cout << p->dataItem;      // Output data
        writeSub(p->next);    // Continue with next node
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::insertEnd(const DT& newDataItem)

// Inserts newDataItem at the end of a list. Moves the cursor to
// newDataItem.

{
    insertEndSub(head, newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::insertEndSub(ListNode<DT>*& p,
    const DT& newDataItem)

    // Recursive partner of the insertEnd() function. Processes the
    // sublist that begins with the node pointed to by p.

{
    if (p != 0)
        insertEndSub(p->next, newDataItem);    // Continue searching for
    else                                     // end of list
    {
        p = new ListNode<DT>(newDataItem, 0);  // Insert new node
        cursor = p;                           // Move cursor
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::writeMirror() const

// Outputs the data in a list from beginning to end and back
// again. Assumes that objects of type DT can be output to the cout
// stream.

{
    cout << "Mirror : ";
    writeMirrorSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::writeMirrorSub(ListNode<DT>* p) const

// Recursive partner of the writeMirror() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if (p != 0)
    {
        cout << p->dataItem;           // Output data (forward)
        writeMirrorSub(p->next);   // Continue with next node
        cout << p->dataItem;           // Output data (backward)
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::reverse()

// Reverses the order of the data items in a list.

{
    reverseSub(0, head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::reverseSub(ListNode<DT>* p, ListNode<DT>* nextP)

// Recursive partner of the reverse() function. Processes the sublist
// that begins with the node pointed to by nextP.

{
    if (nextP != 0)
    {
        reverseSub(nextP, nextP->next);   // Continue with next node
        nextP->next = p;                 // Reverse link
    }
    else
        head = p;                        // Move head to end of list
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>::deleteEnd()

// Deletes the data at the end of a list. Moves the cursor to the
// beginning of the list.

{
    deleteEndSub(head);
    cursor = head;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::deleteEndSub(ListNode<DT>*& p)

// Recursive partner of the deleteEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if (p->next != 0)
        deleteEndSub(p->next);   // Continue looking for the last node
    else
    {
        delete p;                // Delete node
        p = 0;                   // Set p (link or head) to null
    }
}

//--------------------------------------------------------------------

template < class DT >
int List<DT>::getLength() const

// Returns the number of data items in a list.

{
    return getLengthSub(head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
int List<DT>::getLengthSub(ListNode<DT>* p) const

// Recursive partner of the length() function. Processes the sublist
// that begins with the node pointed to by p.

{
    int result;   // Result returned

    if (p == 0)
        result = 0;                            // End of list reached
    else
        result = (getLengthSub(p->next) + 1);   // Number of nodes after
                                               // this one + 1
    return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT >
void List<DT>::cRemove()
{
    cRemoveSub(head);

    if (head != NULL)
        cursor = head;
    else
        cursor = NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT >
void List<DT>::cRemoveSub(ListNode<DT>*& p)
{
    if (p != NULL)
    {
        cRemoveSub(p->next);     // Continue looking for the last node

        if (p->dataItem == 'c')
        {
            if (p == head && p->next == 0)
            {
                delete p;
                head = NULL; cursor = NULL;
            }
            else if (p == head)
            {
                ListNode<DT>* tempPtr = p;
                p = p->next;
                head = p;
                delete tempPtr;
            }
            else if (p->next == 0)
            {
                ListNode<DT>* prevPtr = head;

                while (prevPtr->next != p)
                {
                    prevPtr = prevPtr->next;
                }

                delete p;
                prevPtr->next = NULL;
            }
            else
            {
                ListNode<DT>* nextPtr = p->next;
                ListNode<DT>* prevPtr = head;

                while (prevPtr->next != p)
                {
                    prevPtr = prevPtr->next;
                }

                delete p;
                prevPtr->next = nextPtr;
                
            }
        }
    }
}