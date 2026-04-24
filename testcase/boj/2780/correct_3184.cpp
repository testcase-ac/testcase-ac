#include <bits/stdc++.h>
using namespace std;
vector<int> adj[10] = {{7},{2,4},{1,3,5},{2,6},{1,5,7},{2,4,6,8},{3,5,9},{4,8,0},{5,7,9},{6,8}};
int dp[1001][10], MOD = 1234567;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<10; i++) {
		dp[1][i] = 1;
	}
	for(int i=2; i<=1000; i++) {
		for(int j=0; j<10; j++) {
			for(int a: adj[j]) {
				dp[i][j] += dp[i-1][a];
			}
			dp[i][j] %= MOD;
		}
	}
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cout << accumulate(dp[n], dp[n]+10, 0) % MOD << '\n';
	}
}
