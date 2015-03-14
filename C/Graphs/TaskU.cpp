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
pair<long long, int> len[5000];
long long visited[5000];
vector<int> infin;
int n, m;

long long dfs(int state) {
    long long x = 0;
    if(visited[state])
        return x = binary_search(infin.begin(), infin.end(), state) ? inf : 1;
    visited[state] = 1;
    for(auto move : edges)
        if(move.first.first == state)
            x = max(dfs(move.first.second), x);
    return x;
}

long long bellman (int state) {
    long long ln;
    len[state] = pair<long long,int>(0, state);
    for(int i = 0; i < n - 1; i++) {
        for (auto move : edges) {
            ln = len[move.first.first].first;
            if (len[move.first.second].first > ln + move.second) {
                len[move.first.second] = pair<long long, int>(ln + move.second, move.first.first);
            }
        }
    }
    for(int i = 0; i < n; i++)
        visited[i] = 0;
    for(auto move : edges) {
        ln = len[move.first.first].first;
        if(len[move.first.second].first > ln + move.second)
            infin.push_back(move.first.first);
    }
    return 0;
}

long long algo(int state, int finState) {
    long long s = bellman(state);
    int x = finState;

    for(int i = 0; i < n; i++)
        visited[i] = 0;
    sort(infin.begin(), infin.end());
    s = dfs(state);
    if(!visited[finState])
        return -1;
    else if(s == inf)
        return inf;
    return -len[x].first;
}

int main()
{
    FILE *in, *out;
    int s, f, l, r, x;
    long long i, k;
    char c, d;
    int stateBeg, stateFin;
    in = fopen("maze.in", "r");
    out = fopen("maze.out", "w");
    fscanf(in, "%d %d\n", &n, &m);

    for(i = 0; i < n; i++) {
        len[i] = pair<long long,int>(inf, -1);
        visited[i] = 0;
    }
    for(i = 0; i < m; i++) {
        fscanf(in, "%d %d %d", &l, &r, &x);
        edges.push_back(pair<pair<int,int>,long long>(pair<int,int>(l - 1, r - 1), -x));
    }

    auto rt = algo(0, n - 1);
    if(rt == -1) {
        fprintf(out, ":(\n");
    } else if (rt == inf)
        fprintf(out, ":)\n");
    else
        fprintf(out,  LLD "\n", rt);

    fclose(in);
    fclose(out);
    return 0;
}
