#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
int dp[5001][5001], sum[5001], chrcnt[26];
int modinv(int a, int b=MOD-2) {
    int ret = 1, mult = a % MOD;
    while(b) {
        if(b&1) ret = (ret*mult)%MOD;
        mult = (mult*mult)%MOD;
        b /= 2;
    }
    return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> s(n), c(n);
	for(int i=0; i<n; i++) {
		cin >> s[i] >> c[i];
	}
	for(int i=0; i<m; i++) {
		char p;
		cin >> p;
		chrcnt[p-'A']++;
	}
	sum[0] = 1;
	for(int i=1; i<=k; i++) {
		for(int j=0; j<n; j++) {
			if(s[j] <= i) {
				dp[i][c[j]] += sum[i-s[j]];
				sum[i] += sum[i-s[j]];
			}
		}
		for(int j=1; j<=n; j++)
			dp[i][j] %= MOD;
		sum[i] %= MOD;
	}
	int ans = 1;
	for(int i=0; i<26; i++) {
		if(!chrcnt[i]) continue;
		int t = 0;
		for(int j=1; j<=n; j++) {
			if(dp[k][j])
				t += modinv(dp[k][j], chrcnt[i]);
		}
		t %= MOD;
		ans = (ans*t)%MOD;
	}
	cout << ans;
}
