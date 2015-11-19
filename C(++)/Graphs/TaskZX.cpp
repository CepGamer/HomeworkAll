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
long long odd[100002];
long long even[100002];

int main()
{
	int s, f, l, r;
	long long x;
	//	long long i;
	char c, d;
	int stateBeg, stateFin;

	n = 0, c = 'a';
	in = fopen("palindrome.in", "r");
	out = fopen("palindrome.out", "w");
	while (fscanf(in, "%c", &str[n]), str[n++]);
	l = 0, r = -1, n--;
	fori odd[i] = even[i] = 0;
	fori{
		k = (i > r ? 0 : min(r - i, odd[l + r - i]));
		while (i + k < n && i - k >= 0 && str[i + k] == str[i - k]) ++k;
		odd[i] = k--;
		if (i + k>r)
			l = i - k, r = i + k;
	}
	l = 0, r = -1;
	fori{
		k = (i > r ? 0 : min(r - i + 1, even[l + r - i + 1])) + 1;
		while (i + k - 1 < n && i - k >= 0 && str[i + k - 1] == str[i - k]) ++k;
		even[i] = --k;
		if (i + k - 1>r)
			l = i - k, r = i + k - 1;
	}
	x = 0;
	fori x += odd[i] + even[i] - 1;
	fprintf(out, LLD, x);
	fclose(in);
	fclose(out);
	return 0;
}