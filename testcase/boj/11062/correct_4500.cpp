#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, sum=0;
		cin >> n;
		for(int i=0; i<n; i++) {
			cin >> dp[i][i];
			sum += dp[i][i];
		}
		if(n == 1) {
			cout << dp[0][0] << '\n';
			continue;
		}
		for(int d=1; d<n; d++) {
			for(int l=0; l+d<n; l++) {
				int r = l+d;
				dp[l][r] = max(dp[l][l] - dp[l+1][r], dp[r][r] - dp[l][r-1]);
			}
		}
		int d = max(dp[0][0] - dp[1][n-1], dp[n-1][n-1] - dp[0][n-2]);
		cout << (sum+d)/2 << '\n';
	}
}
