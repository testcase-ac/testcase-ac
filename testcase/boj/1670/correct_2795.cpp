#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[10001];
const ll MOD = 987654321;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	dp[0] = dp[2] = 1;
	for(int i=4; i<=n; i+=2) {
		for(int k=1; k<i; k++) {
			dp[i] += dp[k-1] * dp[i-1-k];
			dp[i] %= MOD;
		}
	}
	cout << dp[n];
}
