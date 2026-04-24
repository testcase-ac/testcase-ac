#include <bits/stdc++.h>
using namespace std;

long long dp[117];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	dp[1] = dp[2] = dp[3] = 1;
	for(int i=4; i<=116; i++) {
		dp[i] = dp[i-1] + dp[i-3];
	}
	int n;
	cin >> n;
	cout << dp[n];
	
}
