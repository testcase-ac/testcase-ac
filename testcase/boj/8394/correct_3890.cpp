#include <bits/stdc++.h>
using namespace std;

const int MX = 1e7+2;
int dp[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	dp[1] = 1;
	dp[2] = 2;
	for(int i=3; i<=n; i++) {
		dp[i] = (dp[i-1] + dp[i-2])%10;
	}
	cout << dp[n];
}
