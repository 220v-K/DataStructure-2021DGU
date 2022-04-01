
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

    // n개가 존재할 때, n-1번 정렬 완료하면 n번째도 자동으로 정렬되므로, n-1번만 반복함.
    for (int i = 0; i < numKeys - 1; i++)
    {
        min = keyList[i];
        min_index = i;

        // 이미 정렬 완료된 것을 제외한 맨 앞부터의 최솟값을 찾음
        for (int j = i + 1; j < numKeys; j++)
        {
            if (min > keyList[j])
            {
                min = keyList[j];
                min_index = j;
            }
        }

        // 최솟값과 정렬 완료된 것을 제외한 맨 앞의 값을 교체.
        // 최솟값이 자기 자신일 때는 교체하지 않도록 할 수 있으나, 그렇게 하면 항상 비교 연산( if (i == min_index) )을 하기 때문에, 그냥 빼버리는 쪽이 연산의 수가 더 적어짐.
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
    // 맨 앞 값을 pivot으로 잡고
    int pivot = left;
    // pivot을 제외한 맨 왼쪽부터, 맨 오른쪽부터 index를 point 해줄 변수들.
    int i = left + 1, j = right;

    // i, j 포인터가 엇갈리거나, 같아질 때까지.
    while (i < j)
    {
        // i 포인터가 가리키는 놈이 pivot값보다 클 때 멈춤
        while (keyList[i] < keyList[pivot])
            i++;
        // j 포인터가 가리키는 놈이 pivot값보다 작을 때 멈춤
        while (keyList[j] > keyList[pivot])
            j--;

        // 엇갈리지 않았을 때, i, j 둘 다 멈췄다면, 둘이 바꿈.
        if (i < j)
        {
            int temp = keyList[i];
            keyList[i] = keyList[j];
            keyList[j] = temp;
            i++;
            j--;
        }
	}

    // 엇갈렸으면 j와 pivot을 바꿈
    if (i >= j && keyList[pivot] > keyList[j])
    {
        int temp = keyList[pivot];
        keyList[pivot] = keyList[j];
        keyList[j] = temp;
    }

    // 그리고, 바뀐 위치의 pivot을 기준으로 왼쪽과 오른쪽에서 다시 정렬 시작.
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
            // 인접한 두 개의 원소를 비교하여 왼쪽이 더 크면 자리를 바꿈
            if (keyList[j] > keyList[j + 1])
            {
                int temp = keyList[j];
                keyList[j] = keyList[j + 1];
                keyList[j + 1] = temp;
            }
        }
    }
}
