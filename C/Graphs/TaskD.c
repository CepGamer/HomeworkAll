#include <stdio.h>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

long long arr[100000];
long long t[100000];
int n;

void assign(int index, long long x) {
    long long diff = x - arr[--index];
    arr[index] = x;
    while(index < n) {
        t[index] += diff;
        index |= index + 1;
    }
}

long long sum(int l, int r) {
    long long toRet = 0;
    l--; r--;
    while (r >= 0) {
        toRet += t[r];
        r = (r & (r + 1)) - 1;
    }
    while (l >= 0) {
        toRet -= t[l];
        l = (l & (l + 1)) - 1;
    }
    return toRet;
}

int main()
{
    FILE *in, *out;
    long long i, k, index, x, l, r;
    char c;
    in = fopen("sum.in", "r");
    out = fopen("sum.out", "w");
    fscanf(in, LLD " " LLD, &n, &k);

    for(i = 0; i < n; i++) {
        t[i] = arr[i] = 0;
    }

    for (i = 0; i < k; i++) {
        fscanf(in, "%c", &c);
        while (c != 'A' && c != 'Q')
            fscanf(in, "%c", &c);
        if (c == 'A') {
            fscanf(in, LLD " " LLD, &index, &x);
            assign(index, x);
        } else if (c == 'Q'){
            fscanf(in, LLD " " LLD, &l, &r);
            fprintf(out, LLD "\n", sum(l - 1, r));
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
