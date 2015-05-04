#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define fori for(int i=0;i<n;i++)

using namespace std;

constexpr long long inf = 100000ll * 100000ll + 1ll;

long long max(long long a, long long b) {
	return a > b ? a : b;
}

long long min(long long a, long long b) {
	return a < b ? a : b;
}

bool cmpFun(int a, int b)
{
	return a < b;
}

struct edge
{
	edge() : end(0), curcap(0), maxcap(0) {};
	edge(int end, int curcap, int maxcap) : end(end), curcap(curcap), maxcap(maxcap) {};
	int end;
	int curcap;
	int maxcap;
};

int n, m, k, w, h, a;
FILE *in, *out;

int vis[100];
int bestres = 1000000000;
vector<int> cur;
vector<edge> edgs;
int edg[100][100];

int dfs(int p)
{
	int b;
	if (p == h) {
		cur.push_back(p);
		return inf;
	}
	if (vis[p])
		return 0;
	vis[p] = 1;
	for (int i = 0; i < n; i++)
		if (edg[p][i] && (b = dfs(i))) {
			cur.push_back(p);
			return min(edg[p][i], b);
		}
	return 0;
}

int ff()
{
	int a, res = 0;
	cur.clear();
	while (a = dfs(0)) {
		for (int i = cur.size() - 2; i >= 0; i--)
			edg[cur[i]][cur[i + 1]] += a, edg[cur[i + 1]][cur[i]] -= a;
		fori vis[i] = 0;
		res += a;
		a = 0;
		cur.clear();
	}
	return res;
}

void algo() {
	fprintf(out, "%d\n", ff());
}

int main()
{
	int s, f, l, r, x;
	//	long long i;
	char c, d;
	int stateBeg, stateFin;

	in = fopen("flow.in", "r");
	out = fopen("flow.out", "w");
	fscanf(in, "%d\n%d", &n, &m);
	h = n - 1;
	fori
		for (int j = 0; j < n; j++)
			edg[i][j] = 0;
	for (int i = 0; i < m; i++) {
		fscanf(in, "%d %d %d", &s, &f, &l);
		edg[--s][--f] += l;
		edg[f][s] += l;
		edgs.push_back(edge(s, f, l));
	}
	algo();
	for (int i = 0; i < edgs.size(); i++) {
		r = edgs[i].maxcap;
		x = abs(edg[edgs[i].end][edgs[i].curcap] - edg[edgs[i].curcap][edgs[i].end]) / 2;
		r = min(x, r) * (edgs[i].end > edgs[i].curcap ? -1 : 1);
		fprintf(out, "%d\n", (edg[edgs[i].end][edgs[i].curcap] -= r, edg[edgs[i].curcap][edgs[i].end] += r, (r)));
	}
	fclose(in);
	fclose(out);
	return 0;
}
