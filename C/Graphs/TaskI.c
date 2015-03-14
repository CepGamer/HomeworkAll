#include <stdio.h>
#include <string.h>
#include <strings.h>

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

int visited[20000];
int edges[2][400000];
int n, m;

int binsearch(int val, int l, int r) {
    int x = (l + r) / 2;
    if (l > r)
        return -1;
    else if(l == r)
        return l;
    else if (val <= edges[0][x])
        return binsearch(val, l, x);
    else
        return binsearch(val, x + 1, r);
}

void dfs(int vertex, int index) {
    int i = binsearch(vertex, 0, 2 * m - 1);
    if(visited[vertex])
        return;
    visited[vertex] = index;
    if(i == -1)
        return;
    while(edges[0][i] == vertex) {
        dfs(edges[1][i++], index);
    }
}

int algo() {
    int index = 1;
    int origVert = 0;
    do {
        while(visited[origVert++] && origVert < n);
        if(origVert == n && visited[origVert - 1])
            return index - 1;
        dfs(--origVert, index++);
    } while (1);
}

int partition(int l, int r)
{
    int x = edges[0][l];
    int i = l - 1;
    int j = r + 1;
    while(1)
    {
        while (edges[0][--j] > x);
        while (edges[0][++i] < x);
        if (i < j)
        {
            edges[0][i] += edges[0][j];
            edges[0][j] = edges[0][i] - edges[0][j];
            edges[0][i] -= edges[0][j];

            edges[1][i] += edges[1][j];
            edges[1][j] = edges[1][i] - edges[1][j];
            edges[1][i] -= edges[1][j];
        } else
            return j;
    }
}

int quickSort(int l, int r)
{
    if(l < r)
    {
        int q = partition(l, r);
        quickSort(l, q);
        quickSort(q + 1, r);
    }
    return 0;
}

int main()
{
    FILE *in, *out;
    long long i, k, index, x, l, r;
    char c;
    in = fopen("connect.in", "r");
    out = fopen("connect.out", "w");
    fscanf(in, "%d %d", &n, &m);

    for (i = 0; i < n; i++)
        visited[i] = 0;
    for (i = 0; i < m; i++)
        edges[0][i] = edges[1][i] = -1;

    for (i = 0; i < m; i++) {
        int a, b;
        fscanf(in, "%d %d", &a, &b);
        edges[1][2 * i + 1] = edges[0][2 * i] = a - 1;
        edges[0][2 * i + 1] = edges[1][2 * i] = b - 1;
    }

    quickSort(0, 2 * m - 1);
    fprintf(out, "%d\n", algo());
    for(i = 0; i < n; i++)
        fprintf(out, "%d ", visited[i]);
    fclose(in);
    fclose(out);
    return 0;
}
