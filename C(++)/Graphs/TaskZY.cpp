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
int n, m, k, w, h, a;
FILE *in, *out;

int z[200000];
int p[200000];

int main()
{
	int s, f, l, r;
	long long x;
	//	long long i;
	char c, d;
	int stateBeg, stateFin;

	n = 0, c = 'a';
	in = fopen("trans.in", "r");
	out = fopen("trans.out", "w");

	fscanf(in, "%d", &n);
	fori fscanf(in, "%d", &z[i]);

	fori p[i] = 0;
	for (int i = 1; i < n; i++)
		if (z[i])
			for (int j = z[i] - 1; j >= 0 && !p[i + j]; j--)
				p[i + j] = j + 1;

	fori fprintf(out, "%d ", p[i]);
	fclose(in);
	fclose(out);
	return 0;
}
