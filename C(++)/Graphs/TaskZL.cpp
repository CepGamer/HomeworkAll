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

#define N 250
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
	edge(int d, int c, int f, edge* n) : dest(d), cap(c), flow(f), neigh(n) {}
	int dest, cap, flow;
	edge* neigh;
};

int vis[N], tup[N];
int graph[N][N];

bool kuhn(int v) {
	vis[v] = 1;
	for (int i = 0; i < n; i++)
		if (graph[v][i] == -1)
			break;
		else if (tup[graph[v][i]] == -1 || (!vis[tup[graph[v][i]]] && kuhn(tup[graph[v][i]]))) {
			tup[graph[v][i]] = v;
			return true;
		}
	return false;
}

long long algo() {
	int res = 0;
	fori{
		fori
			vis[i] = 0;
		if (kuhn(i))
			res++;
	}

	return res;
}

int main()
{
	int f, r, k;
	long long x;
	//	long long i;
	char d;

	in = fopen("pairs.in", "r");
	out = fopen("pairs.out", "w");

	n = N;
	fori 
		tup[i] = -1;
	fscanf(in, "%d%d", &n, &m);
	fori
		for (int j = 0; j <= m; j++)
			graph[i][j] = -1;
	fori{
		int tmp, j = 0;
		do {
			fscanf(in, "%d", &tmp);
			tmp--;
			if (tmp < 0)
				break;
			graph[i][j++] = tmp;
		} while (tmp != -1);
	}

	fprintf(out, LLD"\n", algo());

	n = m;
	fori
		if (tup[i] != -1)
			fprintf(out, "%d %d\n", tup[i] + 1, i + 1);

	fclose(in);
	fclose(out);
	return 0;
}
