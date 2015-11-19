#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define fori for(long long i=0;i<n;i++)

using namespace std;

//#define LONGLONG
#ifdef LONGLONG
constexpr long long inf = 100000ll * 100000ll + 1ll;
#else
constexpr long long inf = INT_MAX / 2;
#endif

#define N 500
#define M 10000

long long max(long long a, long long b) {
	return a > b ? a : b;
}

long long min(long long a, long long b) {
	return a < b ? a : b;
}

bool cmpFun(long long a, long long b)
{
	return a < b;
}

long long left(long long index)
{
	return index * 2;
}

long long right(long long index)
{
	return index * 2 + 1;
}

long long getmid(long long l, long long r)
{
	return (r + l) / 2;
}

long long n, m;
long long origSum;

FILE *in, *out;

struct node {
	node(){ val = -1, sum = 0; }
	long long val;
	long long sum;
};

node arr[120005];
long long a[30001];

void push(long long v, long long lt, long long rt)
{
	long long mid = getmid(lt, rt);
	if (arr[v].val != -1)
	{
		arr[right(v)].sum = (arr[right(v)].val = arr[v].val) * (rt - mid);
		arr[left(v)].sum = (arr[left(v)].val = arr[v].val) * (mid - lt + 1);
		arr[v].val = -1;
	}
}

void build(long long v, long long l, long long r)
{
	if (l == r)
	{
		arr[v].val = arr[v].sum = a[l];
	}
	else
	{
		long long mid = getmid(l, r);
		build(left(v), l, mid);
		build(right(v), mid + 1, r);
		arr[v].sum = arr[left(v)].sum + arr[right(v)].sum;
	}
}

void assign(long long v, long long lt, long long rt, long long l, long long r, long long x)
{
	long long mid = getmid(lt, rt);
	long long res;
	if (l > r)
		return;
	if (l == lt && r == rt)
	{
		arr[v].sum = (r - l + 1) * (arr[v].val = x);
		return;
	}
	push(v, lt, rt);

	assign(left(v), lt, mid, l, min(r, mid), x);
	assign(right(v), mid + 1, rt, max(mid + 1, l), r, x);
	arr[v].sum = arr[left(v)].sum + arr[right(v)].sum;
}

long long sum(long long v, long long lt, long long rt, long long l, long long r)
{
	long long mid = getmid(lt, rt);
	long long x;
	if (l > r)
		return 0;
	if (l == lt && r == rt)
		return arr[v].sum;

	push(v, lt, rt);
	x = sum(left(v), lt, mid, l, min(r, mid)) + 
		sum(right(v), mid + 1, rt, max(mid + 1, l), r);
	//arr[v].sum = arr[left(v)].sum + arr[right(v)].sum;
	return x;
}

void avg(long long l, long long r)
{
	long long csum = sum(1, 0, n - 1, l, r);
	if (sum(1, 0, n - 1, 0, n - 1) <= origSum)
		csum = static_cast<long long>(ceil(csum / double(r - l + 1)));
	else
		csum = static_cast<long long>(floor(csum / double(r - l + 1)));
	assign(1, 0, n - 1, l, r, csum);
}

long long getarr(long long v, long long lt, long long rt, long long pos)
{
	long long mid = getmid(lt, rt);
	if (lt == rt)
		return arr[v].val;

	push(v, lt, rt);
	if (pos <= mid)
		return getarr(left(v), lt, mid, pos);
	else
		return getarr(right(v), mid + 1, rt, pos);
}

int main()
{
	long long f, r, k, l;
	long long x;
	//	long long i;
	char d;

	in = fopen("middle.in", "r");
	out = fopen("middle.out", "w");

	fscanf(in, LLD LLD, &n, &m);

	fori
	{
		fscanf(in, LLD, &f);
		a[i] = f;
	}
	build(1, 0, n - 1);

	origSum = sum(1, 0, n - 1, 0, n - 1);

	for (long long i = 0; i < m; i++)
	{
		fscanf(in, LLD LLD, &l, &r);
		l--, r--;
		avg(l, r);
	}

	fori
		fprintf(out, LLD " ", getarr(1, 0, n - 1, i));

	fclose(in);
	fclose(out);
	return 0;
}
