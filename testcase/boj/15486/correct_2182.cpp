#include <bits/stdc++.h>
using namespace std;
const int MX = 2e6;
int dp[MX], dpm[MX], t[MX], p[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> t[i] >> p[i];
	}
	for(int i=n-1; i>=0; i--) {
		dp[i] = dpm[i+1];
		if(i+t[i] <= n) {
			dp[i] = max(dp[i], p[i]+dpm[i+t[i]]);
		}
		dpm[i] = max(dp[i], dpm[i+1]);
	}
	cout << dpm[0];
}
