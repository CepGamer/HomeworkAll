#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

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
//bool parent[20000];
int n, m, k;

long long algo() {
    int size = coins.size(), len = coins[size - 1] + 1;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               bool vals[len] = {0};
    int label = 0;
    auto x = coins.begin();
    for (int i = 0; i < len; ++i) {
        if(*x == i + 1) {
            vals[*x++] = false;
            continue;
        }
    }
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
    sort(coins.begin(), coins.end(), myfun);

    fprintf(out, "%s\n", algo() ? "PETYA" : "MISHA");

    fclose(in);
    fclose(out);
    return 0;
}
