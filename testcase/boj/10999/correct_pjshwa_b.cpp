#include <bits/stdc++.h>
using namespace std;

long long dat[1000005];

namespace lazyprop1
{
	// example implementation of sum tree
	const int TSIZE = 1048576; // always 2^k form && n <= TSIZE
	long long segtree[TSIZE * 2], prop[TSIZE * 2];
	pair<int, int> segment[TSIZE * 2];
	tuple<int, int, int> que[10000];
	int stk[10000];

	void seg_init(int nod, int l, int r)
	{
		segment[nod] = { l, r };
		if (l == r)
		{
			segtree[nod] = dat[l];
			return;
		}

		int m = (l + r) >> 1;
		seg_init(nod << 1, l, m);
		seg_init(nod << 1 | 1, m + 1, r);
		segtree[nod] = segtree[nod << 1] + segtree[nod << 1 | 1];
	}
	void seg_relax(int nod) {
		int l = segment[nod].first; int r = segment[nod].second;
		if (prop[nod] == 0) return;
		if (l < r) {
			int m = (l + r) >> 1;
			segtree[nod << 1] += (m - l + 1) * prop[nod];
			prop[nod << 1] += prop[nod];
			segtree[nod << 1 | 1] += (r - m) * prop[nod];
			prop[nod << 1 | 1] += prop[nod];
		}

		prop[nod] = 0;
	}
	long long seg_query(int s, int e) {
		int head = 0, tail = 0;
		long long ret = 0;
		que[tail++] = make_tuple(1, s, e);

		while (head < tail)
		{
			int nod;
			tie(nod, s, e) = que[head++];
			int l, r;
			tie(l, r) = segment[nod];

			if (r < s || e < l) continue;
			if (s <= l && r <= e)
			{
				ret += segtree[nod];
				continue;
			}

			seg_relax(nod);

			que[tail++] = make_tuple(nod << 1, s, e);
			que[tail++] = make_tuple(nod << 1 | 1, s, e);
		}
		return ret;
	}
	void seg_update(int s, int e, long long val) {
		int head = 0, tail = 0, top = 0;
		que[tail++] = make_tuple(1, s, e);

		while (head < tail)
		{
			int nod;
			tie(nod, s, e) = que[head++];
			int l, r;
			tie(l, r) = segment[nod];

			if (r < s || e < l) continue;

			if (s <= l && r <= e) {
				segtree[nod] += (r - l + 1) * val;
				prop[nod] += val;
				continue;
			}

			stk[top++] = nod;

			seg_relax(nod);

			int m = (l + r) >> 1;

			que[tail++] = make_tuple(nod << 1, s, e);
			que[tail++] = make_tuple(nod << 1 | 1, s, e);
		}

		while (top)
		{
			int n = stk[--top];
			segtree[n] = segtree[n << 1] + segtree[n << 1 | 1];
		}
	}
}
#define lp lazyprop1

namespace fio {
	const int BSIZE = 524288;
	unsigned char buffer[BSIZE];
	int p = BSIZE;
	inline unsigned char readChar() {
		if (p == BSIZE) {
			fread(buffer, 1, BSIZE, stdin);
			p = 0;
		}
		return buffer[p++];
	}
	template <typename T>
	void readInt(T &ret) {
		unsigned char c = readChar();
		while (c < '-') {
			c = readChar();
		}
		ret = 0; bool neg = c == '-';
		if (neg) c = readChar();
		while (c >= '-') {
			ret = ret * 10 + c - '0';
			c = readChar();
		}
		if (neg) ret = -ret;
	}
}

int main()
{
	int n, m, k;
	fio::readInt(n);
	fio::readInt(m);
	fio::readInt(k);
	m += k;

	for (int i = 0; i < n; i++)
	{
		fio::readInt(dat[i]);
	}

	lp::seg_init(1, 0, n - 1);

	while (m--)
	{
		int t;
		fio::readInt(t);
		if (t == 1)
		{
			int a, b; long long c;
			fio::readInt(a);
			fio::readInt(b);
			fio::readInt(c);
			lp::seg_update(a - 1, b - 1, c);
		}
		else
		{
			int a, b;
			fio::readInt(a);
			fio::readInt(b);
			printf("%lld\n", lp::seg_query(a - 1, b - 1));
		}
	}
}
