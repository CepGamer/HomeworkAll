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

struct state {
	pair<int, int> termPos, survPos;
	int termStep;
};

state makeState(int i, int j, int k, int l, bool termStep)
{
	state toRet;
	toRet.termPos = make_pair(i, j);
	toRet.survPos = make_pair(k, l);
	toRet.termStep = termStep;
	return toRet;
}

int n, m, k, w, h;
bool map[8][8];
bool win[8][8][8][8 + 1][2];
bool lose[8][8][8][8 + 1][2];
bool vis[8][8][8][8 + 1][2];
int deg[8][8][8][8 + 1][2];
vector<state> moves[8][8][8][8 + 1][2];

int survDead(int i, int j, int k, int l) {
	int a = k - i;
	int b = l - j;
	if (a == 0 && b == 0)
		return true;
	if (a == 0 || b == 0 || abs(a) == abs(b)) {
		int bound = max(abs(a), abs(b));
		a /= bound;
		b /= bound;
		for (int m = 1; m < bound; m++)
			if (!map[i + a * m][j + b * m])
				return false;
		return true;
	}
	return false;
}

void step(state curr) {
	bool cur;
	state temp;
	int i = curr.termPos.first, j = curr.termPos.second, k = curr.survPos.first, l = curr.survPos.second;
	int st = curr.termStep;

	vis[i][j][k][l][st] = true;

	for (auto x : moves[i][j][k][l][st])
	{
		int ii = x.termPos.first, ij = x.termPos.second, ik = x.survPos.first, il = x.survPos.second;
		if (vis[ii][ij][ik][il][x.termStep])
			continue;

		if (lose[i][j][k][l][st])
			win[ii][ij][ik][il][x.termStep] = true;
		else if (--deg[ii][ij][ik][il][x.termStep] == 0)
			lose[ii][ij][ik][il][x.termStep] = true;
		else
			continue;

		step(x);
	}

	return;
}

bool checkPos(int ii, int ij, int ik, int il)
{
	return (ii >= 0 && ii < 8 && ij >= 0 && ij < 8 && map[ii][ij] &&
		ik >= 0 && ik < 8 && il >= 0 && il <= 8 && map[ik][il]);
}

bool algo(state init) {
	for (int i = 0; i < 8 * 8; i++)
		for (int k = 0; k < 8 * 8 + 8; k++) 
			for (int st = 0; st < 2; st++)
			{
				bool shoot = survDead(i % 8, i / 8, k % 8, k / 8);
				state next;
				int ii = i % 8, ij = i / 8, ik = k % 8, il = k / 8;
				const int dx[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
				const int dy[] = { 0, 1, 0, -1, -1, 1, -1, 1 };

				bool wn = false, ls = false;

				if (!checkPos(ii, ij, ik, il))
					continue;

				if (st)
					wn = shoot, ls = !shoot && (il == 8);
				else
					ls = shoot, wn = !shoot && (il == 8);

				win[ii][ij][ik][il][st] = wn;
				lose[ii][ij][ik][il][st] = ls;

				if (ls || wn)
					continue;

				auto thiss = makeState(ii, ij, ik, il, /*!*/st);
				//moves[ii][ij][ik][il][st].push_back(thiss);
				//thiss.termStep = st;
				//deg[ii][ij][ik][il][st] = 1;

				for (int step = 0; step < 8; step++)
				{
					if (st)
					{
						if (checkPos(ii + dx[step], ij + dy[step], ik, il))
						{
							moves[ii + dx[step]][ij + dy[step]][ik][il][!st].push_back(thiss);
							deg[ii][ij][ik][il][st]++;
						}
					}
					else
					{
						if (checkPos(ii, ij, ik + dx[step], il + dy[step]))
						{
							moves[ii][ij][ik + dx[step]][il + dy[step]][!st].push_back(thiss);
							deg[ii][ij][ik][il][st]++;
						}
					}
				}
			}
		

	//	start dfs
	for (int i = 0; i < 8 * 8; i++)
		for (int k = 0; k < 8 * 8 + 8; k++)
			for (int st = 0; st < 2; st++)
				if (!vis[i % 8][i / 8][k % 8][k / 8][st] && (lose[i % 8][i / 8][k % 8][k / 8][st] || win[i % 8][i / 8][k % 8][k / 8][st]))
					step(makeState(i % 8, i / 8, k % 8, k / 8, st));

	return win[init.termPos.first][init.termPos.second][init.survPos.first][init.survPos.second][init.termStep];
}

int main()
{
	FILE *in, *out;
	int s, f, l, r, x;
	//	long long i;
	char c, d;
	int stateBeg, stateFin;
	state toPass;

	in = fopen("terminator.in", "r");
	out = fopen("terminator.out", "w");

	for (int i = 0; i < 8 * 8; i++)
		for (int k = 0; k < 8 * 8; k++)
			for (int st = 0; st < 2; st++)
			{
				vis[i % 8][i / 8][k % 8][k / 8][st] = lose[i % 8][i / 8][k % 8][k / 8][st] = win[i % 8][i / 8][k % 8][k / 8][st] = false;
				deg[i % 8][i / 8][k % 8][k / 8][st] = 0;
				moves[i % 8][i / 8][k % 8][k / 8][st].clear();
			}

	for (auto i = 0; i < 8; i++) {
		for (auto j = 0; j < 8; j++) {
			char c;
			fscanf(in, "%c", &c);
			c -= '0';
			switch (c)
			{
			case 2:
				toPass.survPos = make_pair(j, i);
				map[j][i] = true;
				break;
			case 3:
				toPass.termPos = make_pair(j, i);
				map[j][i] = true;
				break;
			case 1:
				map[j][i] = false;
				break;
			case 0:
				map[j][i] = true;
				break;
			default:
				j--;
				break;
			}
		}
	}
	toPass.termStep = 0;

	fprintf(out, algo(toPass) ? "1" : "-1");

	fclose(in);
	fclose(out);
	return 0;
}
