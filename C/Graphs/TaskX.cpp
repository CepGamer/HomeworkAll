#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

long long max (long long a, long long b) {
    return a > b ? a : b;
}

long long min (long long a, long long b) {
    return a < b ? a : b;
}

constexpr long long inf = 100000ll*100000ll+1ll;

vector<pair<pair<int,int>,long long> > edges;
//long long visited[20000];
int parent[20000];
int n, m;

int findSet(int vertex) {
    while(vertex != parent[vertex])
        vertex = parent[vertex] = findSet(parent[vertex]);
    return vertex;
}

void unite(int seta, int setb) {
    int x = findSet(seta);
    int y = findSet(setb);
    if(x != y)
        parent[y] = x;
}

long long kruskal() {
    long long ln = 0;
    for(auto edge : edges) {
        int a, b;
        if((a = findSet(edge.first.first)) != (b = findSet(edge.first.second))) {
            ln += edge.second;
            unite(a, b);
        }
    }
    return ln;
}

long long algo() {
    return kruskal();
}

bool myfun(pair<pair<int,int>,long long> a, pair<pair<int,int>,long long> b) {
    return a.second < b.second;
}

int main()
{
    FILE *in, *out;
    int s, f, l, r, x;
    long long i, k;
    char c, d;
    int stateBeg, stateFin;
    in = fopen("spantree2.in", "r");
    out = fopen("spantree2.out", "w");
    fscanf(in, "%d %d\n", &n, &m);

    for(i = 0; i < n; i++) {
        parent[i] = (int)i;
    }
    for(i = 0; i < m; i++) {
        fscanf(in, "%d %d %d", &l, &r, &x);
        edges.push_back(pair<pair<int,int>,long long>(pair<int,int>(l - 1, r - 1), x));
    }

    sort(edges.begin(), edges.end(), myfun);

    fprintf(out, LLD "\n", algo());

    fclose(in);
    fclose(out);
    return 0;
}
