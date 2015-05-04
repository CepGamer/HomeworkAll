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
	edge(int end, int curcap, int maxcap) : end(end), curcap(curcap), maxcap(maxcap) {};
	int end;
	int curcap;
	int maxcap;
};

int n, m, k, w, h, a;
vector<vector<edge>> edg;
vector<int> fstp, secp, cur;
int vis[100000];
FILE *in, *out;

int dfs(int p)
{
	int a, b;
	if (p == h) {
		cur.push_back(p);
		return inf;
	}
	if (vis[p])
		return 0;
	vis[p] = 1;
	for (int i = 0; i < edg[p].size(); i++)
		if ((a = edg[p][i].maxcap - edg[p][i].curcap) && (b = dfs(edg[p][i].end))) {
			edg[p][i].curcap++;
			return min(a, b);
		}
	return 0;
}

int ff()
{
	int a, res = 0;
	cur.clear();
	while (a = dfs(0)) {
		fori vis[i] = 0;
		res += a;
		a = 0;
		cur.clear();
	}
	return res;
}

void algo() {
	int res;
	res = ff();
	if (res < 2){
		fprintf(out, "NO");
		return;
	}
}

int main()
{
	int s, f, l, r, x;
	//	long long i;
	char c, d;
	int stateBeg, stateFin;

	in = fopen("snails.in", "r");
	out = fopen("snails.out", "w");
	fscanf(in, "%d %d %d %d", &n, &m, &a, &h);
	a--;
	h--;
	for (int i = 0; i < n; i++){
		edg.push_back(vector<edge>());
		edg[i].clear();
	}
	for (int i = 0; i < m; i++) {
		fscanf(in, "%d %d", &s, &f);
		edg[--s].push_back(edge(--f, 0, 1));
	}
	algo();

	fclose(in);
	fclose(out);
	return 0;
}
