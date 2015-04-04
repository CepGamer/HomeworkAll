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

constexpr long long inf = 100000ll*100000ll+1ll;

long long max (long long a, long long b) {
    return a > b ? a : b;
}

long long min (long long a, long long b) {
    return a < b ? a : b;
}

bool cmpFun(int a, int b)
{
	return a < b;
}

int n, m, k, w, h;
set<int> vals;
int states[100];

int mex() {
	for (int i = 0; ; i++)
		if (!vals.count(i))
			return i;
}

int inside(int size)
{
	int toRet = 0;
	bool zero = false, one = false;
	if (states[size] != -1)
		return states[size];
	vals.clear();
	for (int i = 2; i <= size - 1; i++)
		vals.insert(inside(size - i - 1) ^ inside(i - 2));
	vals.insert(inside(size - 2));
	return states[size] = mex();
}

int algo() {
	int x = n > 52 ? 52 + (n - 52) % 34 : n;
	for (int i = 0; i < 100; i++)
		states[i] = -1;
	states[0] = 0;
	for (int i = 1; i < 100; i++)
		states[i] = inside(i);

	return states[x];
}

int main()
{
    FILE *in, *out;
    int s, f, l, r, x;
    long long i;
    char c, d;
    int stateBeg, stateFin;
    in	= fopen("pawns.in", "r");
    out = fopen("pawns.out", "w");
    fscanf(in, "%d\n", &n);

	fprintf(out, algo() ? "White" : "Black");

    fclose(in);
    fclose(out);
    return 0;
}
