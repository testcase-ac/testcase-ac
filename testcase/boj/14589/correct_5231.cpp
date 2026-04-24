#include <bits/stdc++.h>
using namespace std;
#define int long long
const int LOG = 20;
int dp[LOG][300000];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<pair<int, int>> a(n), ast;
	vector<int> num(2*n);
	for(int i=0; i<n; i++) {
		cin >> a[i].first >> a[i].second;
		num[2*i] = a[i].first;
		num[2*i+1] = a[i].second;
	}
	sort(num.begin(), num.end());
	num.erase(unique(num.begin(), num.end()), num.end());
	for(int i=0; i<n; i++) {
		a[i].first = lower_bound(num.begin(), num.end(), a[i].first) - num.begin();
		a[i].second = lower_bound(num.begin(), num.end(), a[i].second) - num.begin();
	}
	ast = a;
	sort(ast.begin(), ast.end());
	int mx = 0;
	for(int i=0, j=0; i<num.size(); i++) {
		while(j < ast.size() && ast[j].first == i) {
			mx = max(mx, ast[j].second);
			j++;
		}
		dp[0][i] = mx;
		//printf("nxt of %d is %d\n", i, mx);
	}
	for(int i=1; i<LOG; i++) {
		for(int j=0; j<num.size(); j++) {
			dp[i][j] = dp[i-1][dp[i-1][j]];
		}
	}
	int q;
	cin >> q;
	while(q--) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		if((a[y].first <= a[x].first && a[x].first <= a[y].second) || (a[y].first <= a[x].second && a[x].second <= a[y].second) || (a[x].first <= a[y].first && a[y].first <= a[x].second)) {
			cout << "1\n";
			continue;
		}
		if(a[x].first > a[y].first)
			swap(x, y);
		int t = a[x].second, ans = 2;
		for(int i=LOG-1; i>=0; i--) {
			if(dp[i][t] < a[y].first) {
				t = dp[i][t];
				ans += (1<<i);
			}
		}
		cout << (ans > n ? -1ll : ans) << '\n';
	}
}
