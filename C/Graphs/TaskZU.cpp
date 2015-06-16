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

int n, m, k, w, h, a;
long long azaz = 0;
FILE *in, *out;

char s[1];
char sub[1];
int z[2];

struct node {
	int l, r, par, link;
	int next[27];

	node(int l = 0, int r = 0, int par = -1) :l(l), r(r), par(par), link(-1) { for (int i = 0; i < 27; i++) next[i] = -1; }
	int len() { return r - l; }
	int &get(char c) { return next[c == '$' ? 26 : c - 'a']; }
};

node t[2];
int sz;

struct state
{
	int v, pos;
	state(int v, int pos) : v(v), pos(pos){}
};

state ptr(0, 0);

state go(state st, int l, int r) {
	while (l < r)
		if (st.pos == t[st.v].len()) {
			st = state(t[st.v].get(s[l]), 0);
			if (st.v == -1) return st;
		} else {
			if (s[t[st.v].l + st.pos] != s[l])
				return state(-1, -1);
			if (r - l < t[st.v].len() - st.pos)
				return state(st.v, st.pos + r - l);
			l += t[st.v].len() - st.pos;
			st.pos = t[st.v].len();
		}
	return st;
}

int split(state st) {
	if (st.pos == t[st.v].len())
		return st.v;
	if (st.pos == 0)
		return t[st.v].par;
	node v = t[st.v];
	int id = sz++;
	t[id] = node(v.l, v.l + st.pos, v.par);
	t[v.par].get(s[v.l]) = id;
	t[id].get(s[v.l + st.pos]) = st.v;
	t[st.v].par = id;
	t[st.v].l += st.pos;
	return id;
}

int get_link(int v) {
	if (t[v].link != -1)
		return t[v].link;
	if (t[v].par == -1)
		return 0;
	int to = get_link(t[v].par);
	return t[v].link = split(go(state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r));
}

void tree_extend(int pos) {
	while (true) {
		state nptr = go(ptr, pos, pos + 1);
		if (nptr.v != -1) {
			ptr = nptr;
			return;
		}
		int mid = split(ptr);
		int leaf = sz++;
		t[leaf] = node(pos, n, mid);
		t[mid].get(s[pos]) = leaf;
		ptr.v = get_link(mid);
		ptr.pos = t[ptr.v].len();
		if (!mid)
			break;
	}
}

void build_tree() {
	sz = 1;
	for (int i = 0; i < n; i++)
		tree_extend(i);
}

int col[100001];
int d[100001];

void algo()
{
	int l = 0, r = -1, k;
	fori {
		if(i > r)
			k = 0;
		else
			k = min(d[l + r - i + 1], r - i + 1);
		while(i + k < n && i - k - 1 >= 0 && col[i + k] == col[i - k - 1])
			k++;
		d[i] = k;
		if(i + k - 1 > r) {
			l = i - k;
			r = i + k - 1;
		}
	}
}

int main()
{
	int f, l, r, k;
	long long x;
	//	long long i;
	int stateBeg, stateFin;

	n = 0;
	in = fopen("cubes.in", "r");
	out = fopen("cubes.out", "w");

	fscanf(in, "%d %d\n", &n, &m);
	fori {
		fscanf(in, "%d", &col[n - i - 1]);
	}
	
	algo();
	
	for(int i = 1; i < n; i++)
		if(d[i] + i == n)
			fprintf(out, "%d ", i);
	fprintf(out, "%d", n);
	
	fclose(in);
	fclose(out);
	return 0;
}
