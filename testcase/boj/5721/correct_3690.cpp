#include <bits/stdc++.h>
using namespace std;
int solve(vector<int>& v) {
	int n = v.size();
	vector<int> dp(n);
	dp[0] = v[0];
	if(n >= 2)
		dp[1] = max(v[0], v[1]);
	for(int i=2; i<n; i++) {
		dp[i] = max(v[i]+dp[i-2], dp[i-1]);
	}
	return dp.back();
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m, n;
	while(cin >> m >> n) {
		if(!m && !n) break;
		vector<vector<int>> arr(m, vector<int>(n));
		vector<int> v(m);
		for(int i=0; i<m; i++) {
			for(int j=0; j<n; j++) {
				cin >> arr[i][j];
			}
			v[i] = solve(arr[i]);
		}
		cout << solve(v) << '\n';
	}
}
