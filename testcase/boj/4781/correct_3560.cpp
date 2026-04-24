#include <bits/stdc++.h>
using namespace std;
// dp[n][p] = max(dp[n-1][p-k*a[i]]+k*c[i] for all k>=0 s.t. p-k*a[i]>=0)
int top(string &s) {
	int ret = 0;
	for(char c: s) {
		if(c == '.') continue;
		ret *= 10;
		ret += c-'0';
	}
	return ret;
}
int dp[2][10001];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	string s;
	while(1) {
		cin >> n >> s;
		if(n == 0 && s == "0.00") break;
		int total = top(s);
		memset(dp, 0, sizeof dp);
		for(int i=1; i<=n; i++) {
			int cur = i&1, prv = cur^1;
			int c, p;
			cin >> c >> s;
			p = top(s);
			for(int j=1; j<p; j++)
				dp[cur][j] = dp[prv][j];
			for(int j=p; j<=total; j++)
				dp[cur][j] = max(dp[prv][j], dp[cur][j-p]+c);
		}
		cout << dp[n&1][total] << '\n';
	}
}
