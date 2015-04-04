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

vector<int> coins;
set<int> temp;
int n, m, k;
bool states[10000];

bool algo() {
	if (n == 0)
		return false;
    for(int i = 0; i < n; i++)
        states[i] = true;
    for (int i = n - 1; i >= 0; i--) {
		auto prstate = states[i];
        for (auto item : coins)
            states[i] = (i + item >= n ? false : (states[i] && !states[i + item]));
    }
    return !states[0];
}

bool myfun(int a, int b)
{
    return a < b;
}

int main()
{
    FILE *in, *out;
    int s, f, l, r, x;
    long long i;
    char c, d;
    int stateBeg, stateFin;
    in = fopen("tickets.in", "r");
    out = fopen("tickets.out", "w");
    fscanf(in, "%d %d\n", &n, &k);

    for(i = 0; i < k; i++) {
        fscanf(in, "%d", &s);
        coins.push_back(s);
    }

    fprintf(out, "%s\n", algo() ? "PETYA" : "MISHA");

    fclose(in);
    fclose(out);
    return 0;
}
