#include <bits/stdc++.h>
using namespace std;
const int MX = 5e5+2;
int a[3][MX], inv[3][MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ans = 0;
	cin >> n;
	for(int j=1; j<=n; j++) {
		cin >> a[0][j];
	}
	for(int i=1; i<3; i++) {
		for(int j=1; j<=n; j++) {
			cin >> a[i][j];
			inv[i-1][a[i][j]] = j;
		}
	}
	map<int,int> dp;
	for(int i=1; i<=n; i++) {
		int t = a[0][i], x = inv[0][t], y = inv[1][t];
		auto it = dp.upper_bound(x);
		while(it != dp.end() && it->second > y)
			it = dp.erase(it);
		if(it == dp.begin() || prev(it)->second > y) {
			ans++;
			dp[x] = y;
		}
	}
	cout << ans;
}
