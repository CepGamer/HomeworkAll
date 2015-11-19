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

#ifdef LONGLONG
constexpr long long inf = 100000ll * 100000ll + 1ll;
#else
constexpr int inf = INT_MAX;
#endif
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

bool cmpFun(int a, int b)
{
	return a < b;
}

int n, m, k, h, l, time;
long long azaz = 0;
FILE *in, *out;

int a[301][301];
int u[301], v[301], p[301], w[301], mv[301], vis[301];

int algo() {
	fori{
		int j0 = 0;
		p[0] = i + 1;
		fori
			mv[i] = inf, vis[i] = 0;
		mv[n] = inf, vis[n] = 0;
		do {
			int i0 = p[j0], d = inf, j1;
			vis[j0] = 1;
			for (int j = 1; j <= n; j++)
				if (!vis[j]) {
					int c = a[i0][j] - u[i0] - v[j];
					if (c < mv[j])
						mv[j] = c, w[j] = j0;
					if (mv[j] < d)
						d = mv[j], j1 = j;
				}
			for (int j = 0; j <= n; j++)
				if (vis[j])
					u[p[j]] += d, v[j] -= d;
				else
					mv[j] -= d;
			j0 = j1;
		} while (p[j0]);
		do{
			int j1 = w[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	return -v[0];
}

int main()
{
	int f, r, k, s, step;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	in = fopen("assignment.in", "r");
	out = fopen("assignment.out", "w");

	fscanf(in, "%d", &n);
	u[0] = v[0] = 0;
	fori
		u[i + 1] = v[i + 1] = 0;
	fori
		for (int j = 0; j < n; j++)
			fscanf(in, "%d", &a[i + 1][j + 1]);

	fprintf(out, "%d\n", algo());

	fori{
		fprintf(out, "%d %d\n", p[i + 1], i + 1);
	}

	fclose(in);
	fclose(out);
	return 0;
}
