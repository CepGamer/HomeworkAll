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
};

int n, m, k, w, h;
int map[8][8];
bool checked[8][8];
int isWin[8];
int states[8][8][8][8][2];
int deg[8][8][8][8][2];
vector<state> checkStates;

vector<state> neighbours(state curr, bool termTurn) {
	vector<state> toRet;
	state temp;
	if (termTurn) {
		if (curr.termPos.first > 0) {
			if (curr.termPos.second > 0) {
				temp = curr;
				temp.termPos.second--;
				if (!map[temp.termPos.first][temp.termPos.second])
					toRet.push_back(temp);

				temp = curr;
				temp.termPos.first--;
				temp.termPos.second--;
				if (!map[temp.termPos.first][temp.termPos.second])
					toRet.push_back(temp);

				if (curr.termPos.first < 7) {
					temp = curr;
					temp.termPos.first++;
					temp.termPos.second--;
					if (!map[temp.termPos.first][temp.termPos.second])
						toRet.push_back(temp);
				}
			}
			temp = curr;
			temp.termPos.first--;
			if (!map[temp.termPos.first][temp.termPos.second])
				toRet.push_back(temp);

			if (curr.termPos.second < 7) {
				temp = curr;
				temp.termPos.first--;
				temp.termPos.second++;
				if (!map[temp.termPos.first][temp.termPos.second])
					toRet.push_back(temp);
			}
		}
		if (curr.termPos.first < 7) {
			temp = curr;
			temp.termPos.first++;
			if (!map[temp.termPos.first][temp.termPos.second])
				toRet.push_back(temp);

			if (curr.termPos.second < 7) {
				temp = curr;
				temp.termPos.first++;
				temp.termPos.second++;
				if (!map[temp.termPos.first][temp.termPos.second])
					toRet.push_back(temp);
			}
		}

		if (curr.termPos.second < 7) {
			temp = curr;
			temp.termPos.second++;
			if (!map[temp.termPos.first][temp.termPos.second])
				toRet.push_back(temp);
		}
		
	}
	else {
		if (curr.survPos.first > 0) {
			if (curr.survPos.second > 0) {
				temp = curr;
				temp.survPos.second--;
				if (!map[temp.survPos.first][temp.survPos.second])
					toRet.push_back(temp);

				temp = curr;
				temp.survPos.first--;
				temp.survPos.second--;
				if (!map[temp.survPos.first][temp.survPos.second])
					toRet.push_back(temp);

				if (curr.survPos.first < 7) {
					temp = curr;
					temp.survPos.first++;
					temp.survPos.second--;
					if (!map[temp.survPos.first][temp.survPos.second])
						toRet.push_back(temp);
				}
			}
			temp = curr;
			temp.survPos.first--;
			if (!map[temp.survPos.first][temp.survPos.second])
				toRet.push_back(temp);

			if (curr.survPos.second < 7) {
				temp = curr;
				temp.survPos.first--;
				temp.survPos.second++;
				if (!map[temp.survPos.first][temp.survPos.second])
					toRet.push_back(temp);
			}
		}
		if (curr.survPos.first < 7) {
			temp = curr;
			temp.survPos.first++;
			if (!map[temp.survPos.first][temp.survPos.second])
				toRet.push_back(temp);

			if (curr.survPos.second < 7) {
				temp = curr;
				temp.survPos.first++;
				temp.survPos.second++;
				if (!map[temp.survPos.first][temp.survPos.second])
					toRet.push_back(temp);
			}
		}

		if (curr.survPos.second < 7) {
			temp = curr;
			temp.survPos.second++;
			if (!map[temp.survPos.first][temp.survPos.second])
				toRet.push_back(temp);
		}
	}

	return toRet;
}

int tempFun(int i, int j, int k, int l, int st) {
	int a = k - i;
	int b = l - j;
	if (map[i][j] || map[k][l])
		return 0;
	if (a == 0 && b == 0)
		return st ? 2 : 1;
	if (a == 0 || b == 0 || abs(a) == abs(b)) {
		int bound = max(abs(a), abs(b));
		a /= bound;
		b /= bound;
		if (map[i + a * bound][j + b * bound])
			return 0;
		for (int m = 1; m < bound; m++)
			if (map[i + a * m][j + b * m])
				goto label;
		return st ? 2 : 1;
	}
	label:
	return l == 7 ? st ? 0 : 2 : 0;
}

void step(int move, state curr) {
	bool cur;
	state temp;
	auto neigh = neighbours(curr, move);
	if (states[curr.termPos.first][curr.termPos.second][curr.survPos.first][curr.survPos.second][move] & 16)
		return;
	states[curr.termPos.first][curr.termPos.second][curr.survPos.first][curr.survPos.second][move] |= 16;
	for (auto item : neigh) {
		if (states[item.termPos.first][item.termPos.second][item.survPos.first][item.survPos.second][1 - move] & 16) 
			continue;
		if (states[curr.termPos.first][curr.termPos.second][curr.survPos.first][curr.survPos.second][move] & 1)
			states[item.termPos.first][item.termPos.second][item.survPos.first][item.survPos.second][1 - move] |= 2;
		else if (--deg[item.termPos.first][item.termPos.second][item.survPos.first][item.survPos.second][1 - move] == 0)
			states[item.termPos.first][item.termPos.second][item.survPos.first][item.survPos.second][1 - move] |= 1;
		else continue;
		step(1 - move, item);
	}
	return ;
}

int checkem(pair<int, int> survPos) {
	if (checked[survPos.first][survPos.second])
		return 0;
	checked[survPos.first][survPos.second] = true;
	if (survPos.first < 0 || survPos.second < 0 || survPos.first > 7 || survPos.second > 7)
		return 0;
	if (map[survPos.first][survPos.second] == 1)
		return 1;
	if (survPos.second == 7)
		return 2;
	return checkem(make_pair(survPos.first + 1, survPos.second)) |
		checkem(make_pair(survPos.first + 1, survPos.second + 1)) |
		checkem(make_pair(survPos.first + 1, survPos.second - 1)) |
		checkem(make_pair(survPos.first, survPos.second + 1)) |
		checkem(make_pair(survPos.first, survPos.second - 1)) |
		checkem(make_pair(survPos.first - 1, survPos.second)) |
		checkem(make_pair(survPos.first - 1, survPos.second + 1)) |
		checkem(make_pair(survPos.first - 1, survPos.second - 1));
}

state makeState(int i, int j, int k, int l)
{
	state toRet;
	toRet.termPos = make_pair(i, j);
	toRet.survPos = make_pair(k, l);

	return toRet;
}

int getDeg(int r, int j, int k, int l, int st)
{
	const int dx[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
	const int dy[] = { 0, 1, 0, -1, -1, 1, -1, 1 };
	int toRet = 0;
	if (states[r][j][k][l][st] & 3)
		return toRet;
	if (map[r][j] || map[k][l])
		return toRet;
	for (int i = 0; i < 8; i++) {
		int ii = r, ij = j, ik = k, il = l;
		if (st)
			ii += dx[i], ij += dy[i];
		else
			ik += dx[i], il += dy[i];
		if (ii >= 0 && ii < 8 && ij >= 0 && ij < 8 && map[ii][ij] == 0 &&
			ik >= 0 && ik < 8 && il >= 0 && il < 8 && map[ik][il] == 0) {
			toRet++;
		}
	}
	return toRet;
}

bool algo(state init) {
	map[init.termPos.first][init.termPos.second] = 0;
	if (!(checkem(init.survPos) & 2))
		return false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 8; k++)
				for (int l = 0; l < 8; l++) {
					states[i][j][k][l][0] = tempFun(i, j, k, l, 0);
					states[i][j][k][l][1] = tempFun(i, j, k, l, 1);
				}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 8; k++)
				for (int l = 0; l < 8; l++)
					for (int st = 0; st < 2; st++)
						deg[i][j][k][l][st] = getDeg(i, j, k, l, st);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 8; k++)
				for (int l = 0; l < 8; l++)
					for (int st = 0; st < 2; st++)
						if (states[i][j][k][l][st] & 3)
							step(st, makeState(i, j, k, l));

	5;
	return states[init.termPos.first][init.termPos.second][init.survPos.first][init.survPos.second][0] & 2;
}

int main()
{
	FILE *in, *out;
	int s, f, l, r, x;
//	long long i;
	char c, d;
	int stateBeg, stateFin;
	state toPass;

	in  = fopen("terminator.in", "r");
	out = fopen("terminator.out", "w");

	for (auto i = 0; i < 8; i++) {
		for (auto j = 0; j < 8; j++) {
			fscanf(in, "%c", &map[i][j]);
			map[i][j] -= '0';
			checked[i][j] = false;
			switch (map[i][j])
			{
			case 2:
				toPass.survPos = make_pair(i, j);
				map[i][j] = 0;
				break;
			case 3:
				toPass.termPos = make_pair(i, j);
				break;
			default:
				break;
			}
		}
		fscanf(in, "\n");
	}

	fprintf(out, algo(toPass) ? "1" : "-1");

	fclose(in);
	fclose(out);
	return 0;
}
