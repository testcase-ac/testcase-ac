#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001], mv[1001][1001], n, w;
pair<int, int> p[1001];
int dist(pair<int, int> a, pair<int, int> b) {
	return abs(a.first-b.first) + abs(a.second - b.second);
}
int main() {
	//ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> w;
	for(int i=1; i<=w; i++)
		cin >> p[i].first >> p[i].second;
	dp[1][0] = dist({1,1}, p[1]);
	dp[0][1] = dist({n,n}, p[1]);
	for(int i=2; i<=w; i++) {
		for(int j=0; j<i-1; j++) {
			int d = dist(p[i-1], p[i]);
			dp[i][j] = dp[i-1][j] + d;
			dp[j][i] = dp[j][i-1] + d;
		}
		dp[i][i-1] = dp[0][i-1] + dist({1,1}, p[i]);
		dp[i-1][i] = dp[i-1][0] + dist({n,n}, p[i]);
		for(int j=1; j<i-1; j++) {
			int d = dist(p[j], p[i]);
			if(dp[j][i-1] + d < dp[i][i-1]) {
				dp[i][i-1] = dp[j][i-1] + d;
				mv[i][i-1] = j;
			}
			if(dp[i-1][j] + d < dp[i-1][i]) {
				dp[i-1][i] = dp[i-1][j] + d;
				mv[i-1][i] = j;
			}
		}
	}
	int ans = 1e9, x = 0, y = 0;
	for(int i=0; i<w; i++) {
		if(dp[i][w] < ans) {
			ans = dp[i][w];
			x = i, y = w;
		}
		if(dp[w][i] < ans) {
			ans = dp[w][i];
			x = w, y = i;
		}
	}
	vector<int> v;
	while(x || y) {
		if(abs(x-y) == 1) {
			if(x > y) {
				x = mv[x][y];
				v.push_back(1);
			} else {
				y = mv[x][y];
				v.push_back(2);
			}
		} else if(x > y) {
			v.push_back(1);
			x--;
		} else {
			v.push_back(2);
			y--;
		}
	}
	reverse(v.begin(), v.end());
	cout << ans << '\n';
	for(int i: v) cout << i << '\n';
}
