#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

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

int n, m, k, w, h;

int grundy(int st) {
	return st % 4 == 3 ? st + 1 : st % 4 == 0 ? st - 1 : st;
}

bool algo() {
	int toRet = 0;
	return false;
}

int main()
{
	FILE *in, *out;
	int s, f, l, r, x;
	long long i;
	char c, d;
	int stateBeg, stateFin;
	in =  fopen("varnim.in", "r");
	out = fopen("varnim.out", "w");
	fscanf(in, "%d\n", &k);
	for (int i = 0; i < k; i++) {
		int x = 0;
		fscanf(in, "%d", &n);
		for (int i = 0; i < n; i++)
		{
			fscanf(in, "%d", &f);
			x ^= grundy(f);
		}
		fprintf(out, x ? "FIRST\n" : "SECOND\n");
	}

	fclose(in);
	fclose(out);
	return 0;
}
