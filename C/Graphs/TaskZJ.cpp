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
	edge(int beg, int end, int cap) : beg(beg), end(end), cap(cap) {};
	int beg, end;
	int cap;
};

int bestres = 1000000000;
int n, m, k, w, h, a;
int edg[100][100];
int vis[100];
FILE *in, *out;
vector<edge> edgs;
vector<int> cur;

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
	int res = 0, c = 0;
	res = ff();
	dfs(0);
	for (auto i : edgs)
		if (vis[i.beg] != vis[i.end])
			c++;
	fprintf(out, "%d %d\n", c, res);
	for (int i = 0; i < edgs.size(); i++)
		if (vis[edgs[i].beg] != vis[edgs[i].end])
			fprintf(out, "%d ", i + 1);
}

int main()
{
	int s, f, l, r, x;
	//	long long i;
	char c, d;
	int stateBeg, stateFin;

	in = fopen("cut.in", "r");
	out = fopen("cut.out", "w");
	fscanf(in, "%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			edg[i][j] = 0;

	h = n - 1;
	for (int i = 0; i < m; i++) {
		fscanf(in, "%d %d %d", &s, &f, &l);
		edg[--s][--f] = l;
		edg[f][s] = l;
		edgs.push_back(edge(s, f, l));
	}
	algo();

	fclose(in);
	fclose(out);
	return 0;
}
