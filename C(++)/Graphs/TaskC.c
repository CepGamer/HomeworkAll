#include <stdio.h>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

long long max (long long a, long long b) {
    return a > b ? a : b;
}

long long min (long long a, long long b) {
    return a < b ? a : b;
}

long long left(long long index)
{
    return index * 2 + 1;
}

long long right(long long index)
{
    return index * 2 + 2;
}

long long parent(long long index)
{
    return (index - 1) / 2;
}

long long arr[400000];
long long n;

long long assignInside(long long v, long long l, long long r, long long index, long long x) {
    long long treeSize, mid;
    long long lt = left(v);
    long long rt = right(v);
    if(l == r)
        return arr[v] = x;
    mid = (l + r) / 2;
    if (index > mid) {
        return arr[v] = arr[lt] + assignInside(rt, mid + 1, r, index, x);
    } else {
        return arr[v] = assignInside(lt, l, mid, index, x) + arr[rt];
    }
}

void assign(long long index, long long x) {
    if (index > n)
        return ;
    assignInside(0, 0, n - 1, index - 1, x);
}

long long sumInside(long long v, long long l, long long r, long long lt, long long rt) {
    long long mid;
    if(lt > rt)
        return 0;
    if(lt == l && rt == r)
        return arr[v];
    mid = (l + r) / 2;
    return sumInside(left(v), l, mid, lt, min(rt, mid)) +
            sumInside(right(v), mid + 1, r, max(lt, mid + 1), rt);
}

long long sum(long long left, long long right) {
    return sumInside(0, 0, n - 1, left - 1, right - 1);
}

int main()
{
    FILE *in, *out;
    long long i, k, index, x, l, r;
    char c;
    in = fopen("sum.in", "r");
    out = fopen("sum.out", "w");
    fscanf(in, LLD " " LLD, &n, &k);

    for(i = 0; i < 2 * n - 1; i++)
        arr[i] = 0;

    for (i = 0; i < k; i++) {
        fscanf(in, "%c", &c);
        while (c != 'A' && c != 'Q')
            fscanf(in, "%c", &c);
        if (c == 'A') {
            fscanf(in, LLD " " LLD, &index, &x);
            assign(index, x);
        } else if (c == 'Q'){
            fscanf(in, LLD " " LLD, &l, &r);
            fprintf(out, LLD "\n", sum(l, r));
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
