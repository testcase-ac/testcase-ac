#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int dp[1001][10001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, c;
	cin >> n >> c;
	dp[1][0] = 1;
	for(int i=2; i<=n; i++) {
		int acc = 0;
		for(int j=0; j<=c; j++) {
			acc += dp[i-1][j];
			if(j >= i) acc -= dp[i-1][j-i];
			if(acc < 0) acc += MOD;
			acc %= MOD;
			dp[i][j] = acc;
		}
	}
	cout << dp[n][c];
}
