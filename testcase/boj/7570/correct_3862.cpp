#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int dp[n+1] = {}, lis = 0;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		dp[t] = dp[t-1]+1;
		lis = max(lis, dp[t]);
	}
	cout << (n-lis);
}
