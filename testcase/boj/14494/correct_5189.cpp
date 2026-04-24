#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[1000][1000];
const ll MOD = 1e9+7;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	dp[0][0] = 1;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			if(i)
				dp[i][j] += dp[i-1][j];
			if(j)
				dp[i][j] += dp[i][j-1];
			if(i && j)
				dp[i][j] += dp[i-1][j-1];
			dp[i][j] %= MOD;
		}
	}
	cout << dp[n-1][m-1];
}
