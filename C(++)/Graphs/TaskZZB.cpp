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
int p[100002], cnt[100002], c[100002];
int pn[100002], cn[100002];

int main()
{
	int s, f, l, r;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	a = 127 - 32 + 2;
	n = 0;
	in = fopen("suffarray.in", "r");
	out = fopen("suffarray.out", "w");

	while (fscanf(in, "%c", &str[n]), str[n++] >= 32);

	n--;
	fori str[i] -= 31;
	str[n] = 0;
	n++;

	for (int i = 0; i < max(n, a); i++)
		cnt[i] = 0;

	fori ++cnt[str[i]];
	for (int i = 1; i < a; i++)
		cnt[i] += cnt[i - 1];

	fori p[--cnt[str[i]]] = i;
	c[p[0]] = 0;
	s = 1;
	for (int i = 1; i < n; i++) {
		if (str[p[i]] != str[p[i - 1]]) ++s;
		c[p[i]] = s - 1;
	}

	for (int step = 0; (h = (1 << step)) < n; step++) {
		fori{
			pn[i] = p[i] - h;
			if (pn[i] < 0)
				pn[i] += n;
		}
		for (int i = 0; i < s; i++)
			cnt[i] = 0;
		fori ++cnt[c[pn[i]]];
		for (int i = 1; i < s; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0, s = 1;
		for (int i = 1; i < n; i++) {
			int md1 = (p[i] + h) % n, md2 = (p[i - 1] + h) % n;
			if (c[p[i]] != c[p[i - 1]] || c[md1] != c[md2]) ++s;
			cn[p[i]] = s - 1;
		}
		fori c[i] = cn[i];
	}
	n--;
	fori fprintf(out, "%d ", p[i + 1] + 1);

	fclose(in);
	fclose(out);
	return 0;
}
