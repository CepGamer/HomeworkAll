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
bool used[2000];
int states[101][101];
int answer[8];

int mex(set<int> *vals) {
	for (int i = 0;; i++)
		if (!vals->count(i))
			return i;
}

int grundy(int wh, int ht) {
	int x = 0;
	for (int i = 0; i < 2000; i++)
		used[i] = false;
	if (states[wh][ht] != -1)
		return states[wh][ht];
	set<int> vals;
	vals.clear();
	for (int k = 1; k < wh; k++)
		for (int l = 1; l < ht; l++) {
			used[states[k][l] ^ states[k][ht - l] ^ states[wh - k][ht]] = true;
			used[states[k][l] ^ states[wh][ht - l] ^ states[wh - k][l]] = true;
			used[states[k][ht] ^ states[wh - k][l] ^ states[wh - k][ht - l]] = true;
			used[states[wh][l] ^ states[k][ht - l] ^ states[wh - k][ht - l]] = true;
		}
	while (used[x++]);
	return states[wh][ht] = x - 1;
}

bool algo() {
	for (int i = 1; i <= 100; i++)
		for (int j = 1; j <= 100; j++)
			states[i][j] = -1;
	for (int i = 0; i <= 100; i++)
		states[1][i] = states[i][1] = 0;

	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= h; j++)
			grundy(i, j);

	int i = w;
	int j = h;
	for (int k = 1; k < w; k++)
		for (int l = 1; l < h; l++)
			if (!(states[k][l] ^ states[k][j - l] ^ states[i - k][j])) {
				int ans[8] = { k, 0, k, h, 0, l, k, l };
				for (int i = 0; i < 8; i++)
					answer[i] = ans[i];
				return true;
			}
			else if (!(states[i][j - l] ^ states[i - k][l] ^ states[k][l])){
				int ans[8] = { 0, l, w, l, k, 0, k, l };
				for (int i = 0; i < 8; i++)
					answer[i] = ans[i];
				return true;
			}
			else if (!(states[k][j] ^ states[i - k][l] ^ states[i - k][j - l])){
				int ans[8] = { k, 0, k, h, k, l, w, l };
				for (int i = 0; i < 8; i++)
					answer[i] = ans[i];
				return true;
			}
			else if (!(states[i][l] ^ states[k][j - l] ^ states[i - k][j - l])){
				int ans[8] = { 0, l, w, l, k, l, k, h };
				for (int i = 0; i < 8; i++)
					answer[i] = ans[i];
				return true;
			}

			return false;
}

int main()
{
	FILE *in, *out;
	int s, f, l, r, x;
	long long i;
	char c, d;
	int stateBeg, stateFin;
	in = fopen("divgame.in", "r");
	out = fopen("divgame.out", "w");
	fscanf(in, "%d %d\n", &w, &h);

	if (algo()) {
		fprintf(out, "Alice\n");
		for (int i = 0; i < 4; i++)
			fprintf(out, "%d ", answer[i]);
		fprintf(out, "\n");
		for (int i = 0; i < 4; i++)
			fprintf(out, "%d ", answer[i + 4]);
	}
	else
		fprintf(out, "Bob");

	fclose(in);
	fclose(out);
	return 0;
}
