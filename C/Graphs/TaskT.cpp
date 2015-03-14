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

vector<vector<pair<int,long long> > > edges;
pair<long long, int> len[5000];
int visited[5000];
int n, m;

void dijkstra (int state) {
    long long ln;
    len[state] = pair<long long,int>(0, state);
    for(int i = 0; i < n; i++) {
        int vert = -1;
        for(int j = 0; j < n; j++) {
            if(!visited[j] && (vert == -1 || len[j].first < len[vert].first))
                vert = j;
        }
        if(len[vert].first == inf)
            break;
        visited[vert] = 1;
        ln = len[vert].first;
        for (auto move : edges[vert]) {
            if (len[move.first].first > ln + move.second) {
                len[move.first] = pair<long long, int>(ln + move.second, vert);
            }
        }
    }
}

vector<int> algo(int state, int finState) {
    vector<int> toRet;
    dijkstra(state);

    if(len[finState].first == inf)
        return toRet;

    while(finState != state) {
        toRet.push_back(finState);
        finState = len[finState].second;
    }
    toRet.push_back(state);
    return toRet;
}

int main()
{
    FILE *in, *out;
    int s, f, l, r, x;
    long long i, k;
    char c, d;
    int stateBeg, stateFin;
    in = fopen("distance.in", "r");
    out = fopen("distance.out", "w");
    fscanf(in, "%d %d\n", &n, &m);
    fscanf(in, "%d %d\n", &s, &f);

    for(i = 0; i < n; i++) {
        edges.push_back(vector<pair<int,long long> >());
        len[i] = pair<long long,int>(inf, -1);
        visited[i] = 0;
    }
    for(i = 0; i < m; i++) {
        fscanf(in, "%d %d %d", &l, &r, &x);
        edges[l - 1].push_back(pair<int,long long>(r - 1, x));
        edges[r - 1].push_back(pair<int,long long>(l - 1, x));
    }

    auto rt = algo(s - 1, f - 1);
    if(rt.size() > 0) {
        fprintf(out, LLD "\n", len[f - 1].first);
        for (i = 0; i < rt.size(); i++) {
            fprintf(out, "%d ", rt[rt.size() - i - 1] + 1);
        }
    } else
        fprintf(out, "-1");

    fclose(in);
    fclose(out);
    return 0;
}
