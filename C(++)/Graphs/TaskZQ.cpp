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

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

bool cmpFun(int a, int b)
{
	return a < b;
}

int n, m, k, w, h, a, l, time;
long long azaz = 0;
FILE *in, *out;

int p[50000][20];
int tin[50000], tout[50000];

vector<int> edg[50000];

int dfs(int v) {
	if (tin[v])
		return 0;
	tin[v] = ++time;
	for (int i = 1; i <= l; i++)
		p[v][i] = p[p[v][i - 1]][i - 1];
	for (auto i : edg[v])
		dfs(i);
	tout[v] = ++time;
	return 0;
}

bool up(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
	if (up(a, b)) return a;
	if (up(b, a)) return b;
	for (int i = l; i >= 0; i--)
		if (!up(p[a][i], b))
			a = p[a][i];
	return p[a][0];
}

int main()
{
	int f, r, k;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	in = fopen("lca.in", "r");
	out = fopen("lca.out", "w");

	fscanf(in, "%d", &n);

	p[0][0] = 0;
	edg[0] = vector<int>();
	for (int i = 1; i < n; i++)
	{
		fscanf(in, "%d", &f);
		p[i][0] = f - 1;
		edg[i] = vector<int>();
		edg[f - 1].push_back(i);
	}

	l = 1;
	while ((1 << l) <= n) l++;
	time = 0;
	dfs(0);
	
	fscanf(in, "%d", &m);
	for (int i = 0; i < m; i++) {
		int l, r;
		fscanf(in, "%d %d", &l, &r);
		fprintf(out, "%d\n", lca(l - 1, r - 1) + 1);
	}

	fclose(in);
	fclose(out);
	return 0;
}
