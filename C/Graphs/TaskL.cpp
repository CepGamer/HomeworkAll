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
int tmin[100000];
//int fup[100000];
std::vector<std::vector<int> > edges;
bool ans[100000];
int n, m, cans;

int index;

int dfs(int vertex, int prev) {
    int children = 0;
    if (visited[vertex])
        return 0;
    tmin[vertex] = visited[vertex] = index++;
    for (auto vert : edges[vertex]) {
        if (vert == prev)
            continue;
        if (visited[vert])
            visited[vertex] = min(visited[vertex], tmin[vert]);
        else {
            dfs(vert, vertex);
            visited[vertex] = min(visited[vertex], visited[vert]);
            if (visited[vert] >= tmin[vertex] && prev != -1 && !ans[vertex]) {
                ans[vertex] = true;
                cans++;
            }
            children++;
        }
    }
    if (prev == -1 && children > 1) {
        ans[vertex] = true;
        cans++;
    }
    return 0;
}

int algo() {
    int origVert = 0;
    index = 1;
    cans = 0;
    do {
        while(visited[origVert++] && origVert < n);
        if(origVert == n && visited[origVert - 1])
            return index - 1;
        dfs(--origVert, -1);
    } while (1);
}

int main()
{
    FILE *in, *out;
    long long i, k, x, l, r;
    char c;
    in = fopen("points.in", "r");
    out = fopen("points.out", "w");
    fscanf(in, "%d %d", &n, &m);

    for (i = 0; i < n; i++) {
        ans[i] = tmin[i] = visited[i] = visited[i] = 0;
        edges.push_back(std::vector<int>());
        edges[i].clear();
    }

    for (i = 0; i < m; i++) {
        int a, b;
        fscanf(in, "%d %d", &a, &b);
        edges[a - 1].push_back(b - 1);
        edges[b - 1].push_back(a - 1);
    }

    algo();
    fprintf(out, "%d\n", cans);
    for (i = 0; i < n; i++)
        if (ans[i])
            fprintf(out, "%d\n", i + 1);
    fclose(in);
    fclose(out);
    return 0;
}
