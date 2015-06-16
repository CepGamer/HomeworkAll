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

int n, m, k, h, l, time, s, t, size;
long long azaz = 0;
FILE *in, *out;

int exc[500], height[500], maxh[500];
int fun[500][500], cap[500][500];

pair<int,int> edg[10000];

int algo() {
	long long res = 0;
	while (true) {
		if (!size)
			fori
			if (i != s && i != t && exc[i] > 0) {
				if (size && height[i] > height[maxh[0]])
					size = 0;
				if (!size || height[i] == height[maxh[0]])
					maxh[size++] = i;
			}
		if (!size)
			break;
		while (size) {
			int i = maxh[size - 1];
			bool pushed = false;
			int tmp = 0;
			for (int j = 0; j < n && exc[i]; j++)
				if (tmp = (cap[i][j] - fun[i][j]) && height[i] == height[j] + 1) {
					int add = min(tmp, exc[i]);
					fun[i][j] += add;
					fun[j][i] -= add;
					exc[i] -= add;
					exc[j] += add;
					if (!exc[i])
						size--;
					pushed = true;
				}
			if (!pushed) {
				height[i] = inf;
				for (int j = 0; j < n; j++)
					if (cap[i][j] - fun[i][j] && height[i] > height[j] + 1)
						height[i] = height[j] + 1;
				if (height[i] > height[maxh[0]]) {
					size = 0;
					break;
				}
			}
		}
	}
	fori
		res += fun[i][t];
	return res;
}

int main()
{
	int f, r, k;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	in = fopen("flow2.in", "r");
	out = fopen("flow2.out", "w");

	fscanf(in, "%d %d", &n, &m);
	s = 0, t = n - 1;
	height[s] = n - 1;
	fori
		for (int j = 0; j < n; j++)
			cap[i][j] = 0;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		fscanf(in, "%d %d %d", &a, &b, &c);
		a--, b--;
		cap[b][a] = cap[a][b] = c;
		edg[i] = make_pair(a, b);
	}
	fori{
		fun[s][i] = cap[s][i];
		fun[i][s] = -fun[s][i];
		exc[i] = cap[s][i];
	}
	size = 0;

	fprintf(out, "%d\n", algo());

	n = m;
	fori
		fprintf(out, "%d\n", fun[edg[i].first][edg[i].second]);

	fclose(in);
	fclose(out);
	return 0;
}
