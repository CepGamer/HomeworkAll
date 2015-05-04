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

FILE *in, *out;
int n, m, k, w, a;

struct edge
{
	edge(int beg, int end, int cap) : beg(beg), end(end), cap(cap) {};
	edge(int beg, int end) : beg(beg), end(end) {};
	int beg, end;
	int cap;
};

struct vert
{
	vert(int key, int pr, int cnt, bool rev, long long sum, long long val) : key(key), pr(pr), cnt(cnt), sum(sum), val(val), rev(rev), l(nullptr), r(nullptr) {};
	int key, pr, cnt;
	long long sum, val;
	bool rev;
	vert *l, *r;
};

vert *root;

inline int cnt(vert *x)
{
	return x ? x->cnt : 0;
}

inline long long sum(vert *x)
{
	return x ? x->sum : 0;
}

inline void upcnt(vert *x)
{
	if (x)
		x->cnt = cnt(x->l) + cnt(x->r) + 1;
}

inline void upsum(vert *x)
{
	if (x)
		x->sum = sum(x->l) + sum(x->r) + x->val;
}

inline void upd(vert *x)
{
	upcnt(x);
	upsum(x);
}

void push(vert *x)
{
	if (x && x->rev) {
		x->rev = false;
		swap(x->l, x->r);
		if (x->l)
			x->l->rev ^= true;
		if (x->r)
			x->r->rev ^= true;
	}
}

void merge(vert *&x, vert *l, vert *r)
{
	push(l);
	push(r);
	if (!l || !r)
		x = l ? l : r;
	else if (l->pr > r->pr)
		merge(l->r, l->r, r), x = l;
	else 
		merge(r->l, l, r->l), x = r;
	upd(x);
}

void split(vert *x, vert *&l, vert *&r, int key, int add = 0)
{
	if (!x)
		return (void)(l = r = nullptr);
	push(x);
	int cur = add + cnt(x->l);
	if (key <= cur)
		split(x->l, l, x->l, key, add), r = x;
	else
		split(x->r, x->r, r, key, add + 1 + cnt(x->l)), l = x;
	upd(x);
}

void insert(vert *&x, vert *t)
{
	if (!x)
		x = t;
	else if (t->pr > x->pr)
		split(x, t->l, t->r, t->key), x = t;
	else
		insert(t->key < x->key ? x->l : x->r, t);
	upd(x);
}

void reverse(vert *x, int l, int r)
{
	vert *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
	split(x, t1, t2, l);
	split(t2, t2, t3, r - l + 1);
	t2->rev ^= true;
	merge(x, t1, t2);
	merge(x, x, t3);
}

long long sum(vert *x, int l, int r)
{
	vert *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
	long long toret;
	split(x, t1, t2, l);
	split(t2, t2, t3, r - l + 1);
	toret = t2->sum;
	merge(x, t1, t2);
	merge(x, x, t3);
	return toret;
}

void algo(int n) {
	int a, b, c;
	fori {
		fscanf(in, "%d %d %d", &a, &b, &c);
		if (a)
			reverse(root, --b, --c);
		else
			fprintf(out, LLD "\n", sum(root, --b ,--c));
	}
}

inline int random()
{
	return (rand() * 10 + rand()) % 200000;
}

int main()
{
	int s, f, l, r, x;
//	long long i;
	char c, d;
	int stateBeg, stateFin;
	root = nullptr;
	srand(42);
	in  = fopen("reverse.in",	"r");
	out = fopen("reverse.out",	"w");
	fscanf(in, "%d %d", &n, &m);
	fori{ 
		fscanf(in, "%d", &s);
		insert(root, new vert(i, random(), 1, false, s, s));
	}
	algo(m);
	fclose(in);
	fclose(out);
	return 0;
}
