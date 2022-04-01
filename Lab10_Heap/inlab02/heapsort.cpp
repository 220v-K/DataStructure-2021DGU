
//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 2                     heapsort.cs
//
//  (Shell) heapSort() function
//
//--------------------------------------------------------------------

template < class DT >
void moveDown(DT dataItem[], int root, int size)

// Restores the binary tree that is rooted at root to a heap by moving
// dataItem[root] downward until the tree satisfies the heap property.
// Parameter size is the number of data items in the array.

{
    int cursor = root;
    int left = cursor * 2 + 1;
    int right = cursor * 2 + 2;

        while (dataItem[left].pty() >= 0)
        {
            //left 자식 노드만 존재할 때
            if (dataItem[right].pty() == 0)
            {
                if (dataItem[left].pty() >= dataItem[cursor].pty())
                {
                    int temppty = dataItem[cursor].pty();          //서로 바꿔줌
                    dataItem[cursor].setPty(dataItem[left].pty());
                    dataItem[left].setPty(temppty);
                    cursor = left;      //커서는 바꿔준 left자식노드로
                }
                else
                    break;
            }
            //left, right 둘 다 존재할 때
            else
            {
                if (dataItem[left].pty() > dataItem[right].pty())
                {
                    if (dataItem[left].pty() >= dataItem[cursor].pty())
                    {
                        int temppty = dataItem[cursor].pty();          //서로 바꿔줌
                        dataItem[cursor].setPty(dataItem[left].pty());
                        dataItem[left].setPty(temppty);
                        cursor = left;      //커서는 바꿔준 left자식노드로
                    }
                    else
                        break;
                }
                else
                {
                    if (dataItem[right].pty() >= dataItem[cursor].pty())
                    {
                        int temppty = dataItem[cursor].pty();          //서로 바꿔줌
                        dataItem[cursor].setPty(dataItem[right].pty());
                        dataItem[right].setPty(temppty);
                        cursor = right;      //커서는 바꿔준 right자식노드로
                    }
                    else
                        break;
                }
            }

            left = cursor * 2 + 1;
            right = cursor * 2 + 2;
        }
}

//--------------------------------------------------------------------

template < class DT >
void heapSort(DT dataItems[], int size)

// Heap sort routine. Sorts the data items in the array in ascending
// order based on priority.

{
    DT temp;   // Temporary storage
    int j;     // Loop counter

    // Build successively larger heaps within the array until the
    // entire array is a heap.

    for (j = (size - 1) / 2; j >= 0; j--)
        moveDown(dataItems, j, size);

    // Swap the root data item from each successively smaller heap with
    // the last unsorted data item in the array. Restore the heap after
    // each exchange.

    for (j = size - 1; j > 0; j--)
    {
        temp = dataItems[j];
        dataItems[j] = dataItems[0];
        dataItems[0] = temp;
        moveDown(dataItems, 0, j);
    }
}

