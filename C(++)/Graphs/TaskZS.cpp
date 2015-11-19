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

char str[100002];
int p[100002], cnt[100002], c[100002];
int pn[100002], cn[100002];

//bool compare(int l, int r, int len, int deg) {
//	return (c[deg][l] == c[deg][r]) && (c[deg][l + len - (1 << deg)] == c[deg][r + len - (1 << deg)]);
//}

int main()
{
	int f, r, k, s, step;
	long long x;
	//	long long i;
	char d;
	int stateBeg, stateFin;

	in = fopen("substrcmp.in", "r");
	out = fopen("substrcmp.out", "w");

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

	fscanf(in, "%d", &k);
	for (int i = 0; i < k; i++)
	{
		int l, r, len, deg, lr, rr;
		deg = 0;
		fscanf(in, "%d %d %d %d", &l, &lr, &r, &rr);
		if (lr - l != rr - r) {
			fprintf(out, "No\n");
			continue;
		}
		while ((1 << deg) < lr - l + 1) deg++;
		//fprintf(out, compare(l - 1, r - 1, lr - l + 1, deg) ? "Yes\n" : "No\n");
	}

	fclose(in);
	fclose(out);
	return 0;
}
