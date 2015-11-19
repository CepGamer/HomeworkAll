#include <stdio.h>
#include <vector>
#include <queue>
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

int visited[10000];
int len[10000];
std::vector<int> ans;
std::vector<std::vector<int> > edges;
int n, m;

int dfs(int vertex) {
    int i = 0;
    if(visited[vertex] < 0)
        return -1;
    if(visited[vertex])
        return 0;
    visited[vertex] = -1;
    for(auto vert : edges[vertex]) {
        if(dfs(vert) == -1)
            return -1;
        len[vertex] = max(len[vertex], len[vert] + 1);
    }
    ans.push_back(vertex);
    visited[vertex] = 1;
    return 0;
}

int topsort() {
    int origVert = 0;
    do {
        while(visited[origVert++] && origVert < n);
        if(origVert == n && visited[origVert - 1])
            return 1;
        if(dfs(--origVert) == -1)
            return 0;
    } while (1);
}

int algo() {
    int lenmax = 0, vertmax = 0, i;
    topsort();
    for(i = 0; i < n; i++) {
        if(lenmax < len[i])
            lenmax = len[vertmax = i];
    }
    return vertmax;
}

int main()
{
    FILE *in, *out;
    long long i, k, x, l, r;
    char c;
    in = fopen("longpath.in", "r");
    out = fopen("longpath.out", "w");
    fscanf(in, "%d %d", &n, &m);

    for (i = 0; i < n; i++) {
        len[i] = visited[i] = 0;
        edges.push_back(std::vector<int>());
        edges[i].clear();
    }

    for (i = 0; i < m; i++) {
        int a, b;
        fscanf(in, "%d %d", &a, &b);
        edges[a - 1].push_back(b - 1);
    }

    fprintf(out, "%d\n", len[algo()]);
    fclose(in);
    fclose(out);
    return 0;
}
