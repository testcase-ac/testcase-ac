#include <bits/stdc++.h>
using namespace std;
const int MX = 2e5;
int a[MX];
typedef long long ll;
ll minxor(int t, int l, int r, int i, int bm) {
	for(;i>=0 && l != r; i--) {
		int m = lower_bound(a+l, a+r, bm|(1<<i)) - a;
		if(t&(1<<i)) {
			if(m != r) {
				l = m;
				bm |= (1<<i);
			}
		} else {
			if(m != l)
				r = m;
			else
				bm |= (1<<i);
		}
	}
	return t^a[l];
}
ll qry(int l, int r, int bm, int bit) {
	if(r-l <= 1 || bit < 0) return 0;
	int m = lower_bound(a+l, a+r, bm|(1<<bit)) - a;
	if(l == m)
		return qry(l, r, bm|(1<<bit), bit-1);
	if(r == m)
		return qry(l, r, bm, bit-1);
	ll ret = qry(l, m, bm, bit-1) + qry(m, r, bm|(1<<bit), bit-1), mn = LLONG_MAX;
	for(int i=l; i<m; i++) {
		mn = min(mn, minxor(a[i], m, r, bit, bm));
	}
	return ret+mn;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a, a+n);
	n = unique(a, a+n) - a;
	cout << qry(0, n, 0, 29);
}
