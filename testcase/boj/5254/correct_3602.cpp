#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3e5+2;
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
    // queries maximum
    int query(int x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
int arr[MX], acc[MX], dp[MX], n;
int solve() {
	for(int i=1; i<=n; i++) {
		acc[i] = acc[i-1] + arr[i];
	}
	LineContainer cht;
	cht.add(arr[1], acc[0]);
	memset(dp, 0, sizeof dp);
	for(int i=2; i<=n; i++) {
		int q = cht.query(i);
		dp[i] = q + acc[n] - acc[i];
		cht.add(arr[i], acc[i-1]-arr[i]*(i-1));
	}
	return *max_element(dp+2, dp+n+1);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	reverse(arr+1, arr+n+1);
	cout << solve() << '\n';
	reverse(arr+1, arr+n+1);
	cout << solve() << '\n';
}
