#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 100001;
int seg[MX*2], n;
void update(int l, int r, int v) {
	l += n, r += n;
	while(l < r) {
		if(l&1) seg[l++] += v;
		if(r&1) seg[--r] += v;
		l /= 2, r /= 2;
	}
}
int query(int t) {
	t += n;
	int ret = 0;
	while(t) {
		ret += seg[t];
		t /= 2;
	}
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> seg[n+i];
	}
	int q;
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int i, j, k;
			cin >> i >> j >> k;
			i--;
			update(i, j, k);
		} else {
			int x;
			cin >> x;
			cout << query(x-1) << '\n';
		}
	}
}
