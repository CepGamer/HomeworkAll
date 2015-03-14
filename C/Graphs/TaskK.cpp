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

int index;

int dfs(int vertex) {
    if(visited[vertex] == -1) {
        ans[index++] = vertex;
        return -1;
    }
    if(visited[vertex])
        return 0;
    visited[vertex] = -1;
    for(auto vert : edges[vertex]) {
        int x = dfs(vert);
        if(x == -1) {
            if(ans[0] == vertex)
                return 1;
            ans[index++] = vertex;
            return -1;
        } else if (x == 1)
            return 1;
    }
    visited[vertex] = 1;
    return 0;
}

int algo() {
    int origVert = 0;
    index = 0;
    do {
        while(visited[origVert++] && origVert < n);
        if(origVert == n && visited[origVert - 1])
            return 0;
        if(dfs(--origVert) == 1)
            return 1;
    } while (1);
}

int main()
{
    FILE *in, *out;
    long long i, k, x, l, r;
    char c;
    in = fopen("cycle.in", "r");
    out = fopen("cycle.out", "w");
    fscanf(in, "%d %d", &n, &m);

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

    if (algo()) {
        fprintf(out, "YES\n");
        for (i = 0; i < index; i++)
            fprintf(out, "%d ", ans[index - i - 1] + 1);
    }
    else
        fprintf(out, "NO");
    fclose(in);
    fclose(out);
    return 0;
}
