#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll mod = 1000000007;

ll dp[13][3501];

ll solve(int height, int count) {
	ll& ret = dp[height][count];
	if (ret != -1)return ret;
	ret = 0;
	for (int i = 0; i < count; i++)
		ret = (ret + solve(height - 1, i) * solve(height - 1, count - i - 1) % mod) % mod;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	for (int i = 0; i <= k; i++) {
		dp[i][0] = 1;
		int len = min((1 << i) - 1, n);
		for (int j = 1; j <= len; j++)dp[i][j] = -1;
	}
	cout << solve(k, n);
}
