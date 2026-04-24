#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Line {
    mutable int k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(int x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // credit: https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
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
const int MX = 2e5+2;
int arr[MX], acc[MX], f[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		acc[i] = acc[i-1] + arr[i];
		f[i] = f[i-1] + i*arr[i];
	}
	LineContainer cht;
	int ans = 0;
	for(int i=1; i<=n; i++) {
		cht.add(1-i, -f[i-1]+(i-1)*acc[i-1]);
		int q = cht.query(acc[i]);
		ans = max(ans, q+f[i]);
	}
	cout << ans;
}
