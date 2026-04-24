#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll dp[1000001], acc;
const int MOD = 1000000000;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	dp[1] = 0;
	for(int i=2; i<=n; i++) {
		dp[i] = acc;
		if(i%2 == 0)
			dp[i]++;
		if(dp[i] == MOD)
			dp[i] = 0;
		acc += dp[i]*i;
		acc %= MOD;
	}
	cout << dp[n];
}
