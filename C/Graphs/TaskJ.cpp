#include <stdio.h>
#include <vector>
#include <algorithm>

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

int visited[100000];
int ans[100000];
std::vector<std::vector<int> > edges;
int n, m;

int binsearch(int val, int l, int r) {
    int x = (l + r) / 2;
    if (l > r)
        return -1;
    else if(l == r)
        return edges[0][x] == val ? l : -1;
    else if (val <= edges[0][x])
        return binsearch(val, l, x);
    else
        return binsearch(val, x + 1, r);
}

int index;

int dfs(int vertex) {
    int i = 0;
    if(visited[vertex] < 0)
        return -1;
    if(visited[vertex])
        return 0;
    visited[vertex] = -1;
//    i = binsearch(vertex, 0, m - 1);
    if(i != -1)
        for(auto vert : edges[vertex]) {
            if(dfs(vert) == -1)
                return -1;
        }
    ans[index++] = vertex;
    visited[vertex] = 1;
    return 0;
}

int algo() {
    int origVert = 0;
    index = 0;
    do {
        while(visited[origVert++] && origVert < n);
        if(origVert == n && visited[origVert - 1])
            return index;
        if(dfs(--origVert) == -1)
            return 0;
    } while (1);
}

int main()
{
    FILE *in, *out;
    long long i, k, index, x, l, r;
    char c;
    in = fopen("topsort.in", "r");
    out = fopen("topsort.out", "w");
    fscanf(in, "%d %d", &n, &m);

//    edges.resize(n);
    for (i = 0; i < n; i++) {
        ans[i] = visited[i] = 0;
        edges.push_back(std::vector<int>());
        edges[i].clear();
    }

    for (i = 0; i < m; i++) {
        int a, b;
        fscanf(in, "%d %d", &a, &b);
        edges[a - 1].push_back(b - 1);
    }
//
//    for(i = 0; i < n; i++)
//        std::sort(edges[i].begin(), edges[i].end());

    if (algo())
        for(i = 0; i < n; i++)
            fprintf(out, "%d ", ans[n - i - 1] + 1);
    else
        fprintf(out, "-1");
    fclose(in);
    fclose(out);
    return 0;
}
