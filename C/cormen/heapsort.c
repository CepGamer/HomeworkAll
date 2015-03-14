#include <stdio.h>

int left(int index)
{
    return index * 2 + 1;
}

int right(int index)
{
    return index * 2 + 2;
}

int parent(int index)
{
    return (index - 1) / 2;
}

/// index, arrSize, arr
void heapify(int index, int arrSize, int * arr)
{
    int largest;
    int i = index;
    int l = left(index);
    int r = right(index);
    if(l < arrSize && arr[l] > arr[index])
        largest = l;
    else
        largest = index;
    if(r < arrSize && arr[r] > arr[largest])
        largest = r;
    if (largest != index)
    {
        arr[index] += arr[largest];
        arr[largest] = arr[index] - arr[largest];
        arr[index] -= arr[largest];
        // printf("%d\n", arr[index]);
        heapify(largest, arrSize, arr);
    }
}

void buildHeap(int arrSize, int * arr)
{
    int i = 0;
    for (i = (arrSize - 1) / 2; i >= 0; --i)
    {
        // printf("%d\n", arr[i]);
        heapify(i, arrSize, arr);
        // printf("\n");
    }
}

void heapSort(int arrSize, int * arr)
{
    int i;
    int * a = arr;
    buildHeap(arrSize, arr);
    for (i = arrSize - 1; i >= 1; --i)
    {
        a[i] += a[0];
        a[0] = a[i] - a[0];
        a[i] -= a[0];
        heapify(0,--arrSize, arr);
    }
}

int main(int argc, char const *argv[])
{
    int i;
    int arr[9] = {5, 3, 17, 10, 84, 19, 6, 22, 9};

    // printf("%d\n", sizeof(arr) / sizeof(int));
    heapSort(sizeof(arr) / sizeof(int), arr);
    for (i = 0; i < 9; ++i)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}
