#include <stdio.h>

int partition(int * arr, int l, int r)
{
    int x = arr[l];
    int i = l - 1;
    int j = r + 1;
    while(1)
    {
        while (arr[--j] > x);
        while (arr[++i] < x);
        if (i < j)
        {
            arr[i] += arr[j];
            arr[j] = arr[i] - arr[j];
            arr[i] -= arr[j];
        } else
            return j;
    }
}

int quickSort(int * arr, int l, int r)
{
    int i = l;
    if(l < r)
    {
        int q = partition(arr, l, r);
        quickSort(arr, l, q);
        quickSort(arr, q + 1, r);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    int arr[12] = {13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21};
    quickSort(arr, 0, 11);
    for (i; i <= 11; ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
