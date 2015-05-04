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

char str[100002];
int pos[100002], suf[100002], lcp[100002];

int main()
{
	int s, f, l, r, k;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	n = 0;
	in = fopen("sufflcp.in", "r");
	out = fopen("sufflcp.out", "w");

	fscanf(in, "%d\n", &n);
	fori fscanf(in, "%c", &str[i]);
	fori{
		fscanf(in, "%d", &suf[i]);
		pos[--suf[i]] = i;
	}
	k = 0;
	fori{
		if (k > 0)
			k--;
		if (pos[i] == n - 1) {
			lcp[n - 1] = -1;
			k = 0;
		}
		else {
			int j = suf[pos[i] + 1];
			while (max(i + k, j + k) < n && str[i + k] == str[j + k])
				k++;
			lcp[pos[i]] = k;
		}
	}

	for(int i = 0; i < n-1; i++)
		fprintf(out, "%d ", lcp[i]);

	fclose(in);
	fclose(out);
	return 0;
}
