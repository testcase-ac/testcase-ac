#include <bits/stdc++.h>
using namespace std;
#define int long long

int f(int N, int t1, int t2) {
	map<tuple<int, int, bool>,int> mp;
	mp[{N, 0, false}] = 1;
	int res = 0;
	while(mp.size()) {
		auto [el, dp] = *mp.rbegin();
		mp.erase(prev(mp.end()));
		auto [n, tcnt, lz] = el;
		if(!lz) {
			if(t2 == -1) {
				if(tcnt >= 0) res += dp;
			} else {
				if(tcnt == 0) res += dp;
			}
		}
		if(!n) continue;
		if(t2 == -1) {
			for(int d=0; d<=n && d<=9; d++) {
				mp[{(n-d)/10, (t1 == d ? tcnt+1 : tcnt-1), d == 0}] += dp;
			}
		} else {
			for(auto d: {t1, t2}) {
				if(d <= n) mp[{(n-d)/10, (t1 == d ? tcnt+1 : tcnt-1), d == 0}] += dp;
			}
		}
	}
	return res;
}

int32_t main() {
	int X, Y;
	cin >> X >> Y;
	int ans = 0;
	for(int d=0; d<=9; d++) {
		ans += f(Y, d, -1) - f(X-1, d, -1);
	}
	for(int d=0; d<=9; d++) {
		for(int e=d+1; e<=9; e++) {
			ans -= f(Y, d, e) - f(X-1, d, e);
		}
	}
	cout << ans;
}
