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

double min (double a, double b) {
    return a < b ? a : b;
}

constexpr long long inf = 100000ll*100000ll+1ll;

double dist(pair<int,int>a, pair<int,int> b) {
    double x = (double)a.first - (double)b.first;
    double y = (double)a.second - (double)b.second;
    return sqrt(x * x + y * y);
}

vector<pair<int,int> > pos;
double minlen[5000];
int visited[5000];
int n, m;

double prima () {
    double toRet = 0;
    double mindist = inf;
    int minvert = -1, vert;
    vert = 0;
    for(int i = 0; i < n - 1; i++) {
        visited[vert] = 1;
        for (int j = 0; j < n; j++) {
            if(visited[j])
                continue;
            minlen[j] = min(minlen[j], dist(pos[vert], pos[j]));
            if ((minlen[j] < mindist)) {
                mindist = minlen[j];
                minvert = j;
            }
        }
        vert = minvert;
        toRet += mindist;
        mindist = inf;
    }
    return toRet;
}

double algo() {
    double x = prima();

    return x;
}

int main()
{
    FILE *in, *out;
    int s, f, l, r, x;
    long long i, k;
    char c, d;
    int stateBeg, stateFin;
    in = fopen("unionday.in", "r");
    out = fopen("unionday.out", "w");
    fscanf(in, "%d\n", &n);

    for(i = 0; i < n; i++) {
        visited[i] = 0;
        minlen[i] = inf;
    }
    for(i = 0; i < n; i++) {
        fscanf(in, "%d %d", &l, &r);
        pos.push_back(pair<int,int>(l, r));
    }

    fprintf(out, "%f", algo());

    fclose(in);
    fclose(out);
    return 0;
}
