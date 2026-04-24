#include <bits/stdc++.h>
using namespace std;
#define int long long
struct pt {
	int w, h;
};
struct line {
	int a, b;
	int eval(int t) {
		return a*t+b;
	}
};

// https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
struct Line {
	mutable int k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(int x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const int inf = LLONG_MAX;
	int div(int a, int b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(int k, int m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	int query(int x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<pt> arr(n), stk;
	for(int i=0; i<n; i++) {
		cin >> arr[i].w >> arr[i].h;
	}
	sort(arr.begin(), arr.end(), [](pt a, pt b){return a.w < b.w;});
	for(pt p: arr) {
		while(stk.size() && stk.back().h <= p.h)
			stk.pop_back();
		stk.push_back(p);
	}
	LineContainer cht;
	int lst = 0;
	for(int i=0; i<stk.size(); i++) {
		pt p = stk[i];
		cht.add(-p.h, -lst);
		lst = -cht.query(p.w);
	}
	cout << lst;
}
