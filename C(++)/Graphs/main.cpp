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

/*
long long max(long long a, long long b) {
	return a > b ? a : b;
}
*/

#define max(a,b) (a>b?a:b)

long long min(long long a, long long b) {
	return a < b ? a : b;
}

bool cmpFun(int a, int b)
{
	return a < b;
}
int n, m, k, w, h, a;
long long azaz = 0;
FILE *in, *out;

char str[20002];
int z[20002];

int countZ(int left)
{
	int maxval = 0;
	left--;
	for (int i = left + 1, l = left, r = left; i < n; i++) {
		z[i] = 0;
		if (i <= r)
			maxval = max(z[i] = min(r - i + 1, z[i - l + left]), maxval);
		while (i + z[i] < n && str[z[i] + left] == str[i + z[i]]) 
			maxval = max(++z[i], maxval);
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return maxval;
}

int main()
{
	int s, f, l, r, k;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	n = 0;
	in = fopen("substr.in", "r");
	out = fopen("substr.out", "w");

	k = 0;
	while (fscanf(in, "%c", &str[n]), str[n++] >= 32);
	str[--n] = 0;
	for (int i = 0; i < n / 2; i++)
		swap(str[i], str[n - i - 1]);
	str[n] = 0;

	for(int i = n; i >= 1; i--) {
		k += (n - i + 1) - countZ(i);
	}

	fprintf(out, "%d", k);

	fprintf(out, "\n%d", azaz);

	fclose(in);
	fclose(out);
	return 0;
}
