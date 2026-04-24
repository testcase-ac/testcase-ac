#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
int mp[256], arr[MX], dp[MX][21][3];

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	mp['H'] = 0;
	mp['P'] = 1;
	mp['S'] = 2;
	int n, k;
	cin >> n >> k;
	for(int i=1; i<=n; i++) {
		char c;
		cin >> c;
		int t = mp[c];
		t = (t+1)%3;
		for(int j=0; j<=k; j++) {
			dp[i][j][0] = dp[i-1][j][0];
			dp[i][j][1] = dp[i-1][j][1];
			dp[i][j][2] = dp[i-1][j][2];
			if(j) {
				dp[i][j][0] = max({dp[i][j][0], dp[i-1][j-1][1], dp[i-1][j-1][2]});
				dp[i][j][1] = max({dp[i][j][1], dp[i-1][j-1][0], dp[i-1][j-1][2]});
				dp[i][j][2] = max({dp[i][j][2], dp[i-1][j-1][0], dp[i-1][j-1][1]});
			}
			dp[i][j][t]++;
		}
	}
	int ans = 0;
	for(int j=0; j<=k; j++) {
		ans = max({ans, dp[n][j][0], dp[n][j][1], dp[n][j][2]});
	}
	cout << ans;
}
