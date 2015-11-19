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

//#define LONGLONG
#ifdef LONGLONG
constexpr long long inf = 100000ll * 100000ll + 1ll;
#else
constexpr int inf = INT_MAX / 2;
#endif

#define N 500
#define M 10000
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

bool cmpFun(int a, int b)
{
	return a < b;
}

int n, m, k, h, l, time, s, t, size;
long long azaz = 0;
FILE *in, *out;

struct edge {
	edge(int d, int c, int f, edge* n, bool i) : dest(d), cap(c), flow(f), neigh(n), isGen(i) {}
	int dest, cap, flow;
	edge* neigh;
	bool isGen;
};

int bloc[N], way[N], ptr[N];
vector<edge *> graph[N];
vector<edge *> edg;

bool bfs() {
	int a = 0, b = 0;
	way[b++] = s;
	fori
		bloc[i] = -1;
	bloc[s] = 0;
	while (a < b && bloc[t] == -1) {
		int v = way[a++];
		for (auto item : graph[v])
			if (bloc[item->dest] == -1 && item->flow < item->cap) {
				way[b++] = item->dest;
				bloc[item->dest] = bloc[v] + 1;
			}
	}
	return bloc[t] != -1;
}

int dfs(int v, int flow) {
	if (v == t)
		return flow;
	for (int &i = ptr[v]; i < graph[v].size(); i++) {
		edge * item = graph[v][i];
		int tmp = min(flow, item->cap - item->flow), add;
		if (bloc[item->dest] != bloc[v] + 1)
			continue;
		add = tmp ? dfs(item->dest, tmp) : 0;
		if (add) {
			item->flow += add;
			item->neigh->flow -= add;
			return add;
		}
	}
	return 0;
}

long long algo() {
	long long res = 0ll;

	while (true) {
		int add;
		if (!bfs())
			break;
		fori
			ptr[i] = 0;
		while (add = dfs(s, inf))
			res += add;
	}
	return res;
}

int main()
{
	int f, r, k;
	long long x;
	//	long long i;
	char d;

	in = fopen("flow.in", "r");
	out = fopen("flow.out", "w");

	fscanf(in, "%d%d", &n, &m);
	s = 0, t = n - 1;
	fori
		graph[i].clear();
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		edge *t1, *t2;
		fscanf(in, "%d%d%d", &a, &b, &c);
		a--, b--;
		t1 = new edge(b, c, 0, nullptr, true);
		t2 = new edge(a, c, 0, t1, false);
		t1->neigh = t2;
		graph[a].push_back(t1);
		graph[b].push_back(t2);
		edg.push_back(t1);
	}

	fprintf(out, LLD"\n", algo());

	n = m;
	fori
		fprintf(out, "%d\n", edg[i]->flow);

	fclose(in);
	fclose(out);
	return 0;
}
