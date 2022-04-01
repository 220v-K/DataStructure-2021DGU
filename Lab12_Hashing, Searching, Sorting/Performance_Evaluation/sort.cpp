
//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//--------------------------------------------------------------------


template < class DT >
void selectionSort(DT keyList[], int numKeys)

// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
    int min;
    int min_index;

    // n���� ������ ��, n-1�� ���� �Ϸ��ϸ� n��°�� �ڵ����� ���ĵǹǷ�, n-1���� �ݺ���.
    for (int i = 0; i < numKeys - 1; i++)
    {
        min = keyList[i];
        min_index = i;

        // �̹� ���� �Ϸ�� ���� ������ �� �պ����� �ּڰ��� ã��
        for (int j = i + 1; j < numKeys; j++)
        {
            if (min > keyList[j])
            {
                min = keyList[j];
                min_index = j;
            }
        }

        // �ּڰ��� ���� �Ϸ�� ���� ������ �� ���� ���� ��ü.
        // �ּڰ��� �ڱ� �ڽ��� ���� ��ü���� �ʵ��� �� �� ������, �׷��� �ϸ� �׻� �� ����( if (i == min_index) )�� �ϱ� ������, �׳� �������� ���� ������ ���� �� ������.
        keyList[min_index] = keyList[i];
        keyList[i] = min;
    }
}

//--------------------------------------------------------------------

template < class DT >
void quickPartition(DT keyList[], int numKeys, int left, int right);

template < class DT >
void quickSort(DT keyList[], int numKeys)

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList, numKeys, 0, numKeys - 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  

template < class DT >
void quickPartition(DT keyList[], int numKeys,
    int left, int right)

    // Recursive partner of the quickSort routine. Partitions the array
    // entries between left and right into two subarrays. One subarray
    // contains the keys that are less than or equal to splitValue, and
    // the other contains the keys that are greater than splitValue.
    // Recursively sorts each of these subarrays.

{
    // �� �� ���� pivot���� ���
    int pivot = left;
    // pivot�� ������ �� ���ʺ���, �� �����ʺ��� index�� point ���� ������.
    int i = left + 1, j = right;

    // i, j �����Ͱ� �������ų�, ������ ������.
    while (i < j)
    {
        // i �����Ͱ� ����Ű�� ���� pivot������ Ŭ �� ����
        while (keyList[i] < keyList[pivot])
            i++;
        // j �����Ͱ� ����Ű�� ���� pivot������ ���� �� ����
        while (keyList[j] > keyList[pivot])
            j--;

        // �������� �ʾ��� ��, i, j �� �� ����ٸ�, ���� �ٲ�.
        if (i < j)
        {
            int temp = keyList[i];
            keyList[i] = keyList[j];
            keyList[j] = temp;
            i++;
            j--;
        }
	}

    // ���������� j�� pivot�� �ٲ�
    if (i >= j && keyList[pivot] > keyList[j])
    {
        int temp = keyList[pivot];
        keyList[pivot] = keyList[j];
        keyList[j] = temp;
    }

    // �׸���, �ٲ� ��ġ�� pivot�� �������� ���ʰ� �����ʿ��� �ٽ� ���� ����.
    if(left < j - 1)
        quickPartition(keyList, numKeys, left, j - 1);
    if(j + 1 < right)
        quickPartition(keyList, numKeys, j + 1, right);
}

//--------------------------------------------------------------------

template < class DT >
void bubbleSort(DT keyList[], int numKeys)
{
    for (int i = numKeys - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            // ������ �� ���� ���Ҹ� ���Ͽ� ������ �� ũ�� �ڸ��� �ٲ�
            if (keyList[j] > keyList[j + 1])
            {
                int temp = keyList[j];
                keyList[j] = keyList[j + 1];
                keyList[j + 1] = temp;
            }
        }
    }
}
