#include <stdio.h>

int countSort(int * arr, int * brr, int k)
{
    int c[k];
    int i = 0;
    int l = 11;//sizeof(arr) / sizeof(int);

    for (i = 0; i < k; ++i)
    {
        c[i] = 0;
    }
    for (i = 0; i < l; ++i)
    {
        c[arr[i] - 1]++;
    }
    for (i = 1; i < k; ++i)
    {
        c[i] += c[i - 1];
    }
    for (i = l - 1; i >= 0; --i)
    {
        brr[c[arr[i] - 1]-- - 1] = arr[i];
    }
}

int main(int argc, char const *argv[])
{
    int i = 0;
    int a[11] = {7, 1, 3, 1, 2, 4, 5, 7, 2, 4, 3};
    int b[11] = {0};

    countSort(a, b, 7);

    for (i = 0; i < 11; ++i)
    {
        printf("%d\n", b[i]);
    }

    return 0;
}
