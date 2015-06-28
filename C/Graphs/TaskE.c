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

int left(int index)
{
    return index * 2 + 1;
}

int right(int index)
{
    return index * 2 + 2;
}

long long arr[400000];
long long op[400000];
int n;
long long origSum;

long long sum(long long left, long long right);

long long assignOpInside(int v, int l, int r, int index, int rgt, long long x) {
    int mid;
    int lt = left(v);
    int rt = right(v);
    if (rgt < index)
        return arr[v] = sum(l + 1, r + 1);
    if(l == r || (index == l && rgt == r) || (op[v] == x)) {
        op[v] = x;
        return arr[v] = x * (r - l + 1ll);
    }
    mid = (l + r) / 2;
    if(op[v] != -1)
        op[lt] = op[rt] = op[v];
    op[v] = -1;
    return arr[v] = assignOpInside(lt, l, mid, index, min(rgt, mid), x) +
            assignOpInside(rt, mid + 1, r, max(index, mid + 1), rgt, x);
}

void assignOp(long long index, long long right, long long x) {
    if (index > n)
        return ;
    assignOpInside(0, 0, n - 1, index - 1, right - 1, x);
}

long long assignInside(int v, int l, int r, int index, int x) {
    long long treeSize, mid;
    long long lt = left(v);
    long long rt = right(v);
    if(l == r)
        return op[v] = arr[v] = x;
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
    long long mid, x;
    if(lt > rt)
        return 0;
    if(op[v] != -1) {
        return op[v] * (rt - lt + 1);
    }
    if(lt == l && rt == r)
        return arr[v];
    mid = (l + r) / 2;
    x = sumInside(left(v), l, mid, lt, min(rt, mid));
    x += sumInside(right(v), mid + 1, r, max(lt, mid + 1), rt);
    return x;
}

long long sum(long long left, long long right) {
    return sumInside(0, 0, n - 1, left - 1, right - 1);
}

void avg(int index, int rt) {
    long long csum = sum(index, rt);
    long long alsum = sum(1, n);
    long long diff = rt - index + 1;
    if (alsum <= origSum && csum % diff)
        csum = csum / diff + 1ll;
    else
        csum = csum / diff;
    assignOp(index, rt, csum);
}

void getarr(int v, int l, int r) {
    int mid = (l + r) / 2;
    int i;
    if (op[v] == -1) {
        getarr(left(v), l, mid);
        getarr(right(v), mid + 1, r);
        return;
    }
    for (i = l; i <= r; i++)
        arr[i] = op[v];
}

int main()
{
    FILE *in, *out;
    int i, k, index, x, l, r;
    char c;
    in = fopen("middle.in", "r");
    out = fopen("middle.out", "w");
    fscanf(in, "%d %d", &n, &k);

    for(i = 0; i < 4 * n; i++) {
        arr[i] = 0;
        op[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int t;
        fscanf(in, "%d", &t);
        assign(i + 1, t);
        origSum += (long long)t;
    }

    for (i = 0; i < k; i++) {
        fscanf(in, "%d %d\n", &l, &r);
        avg(l, r);
    }

    getarr(0, 0, n - 1);
    for(i = 0; i < n; i++)
        fprintf(out, "%d ", (int)arr[i]);

    fclose(in);
    fclose(out);
    return 0;
}
