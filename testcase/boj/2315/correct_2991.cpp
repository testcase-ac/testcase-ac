#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000][2], pos[1000], wat[1000], n;
int solve(int l, int r, int m) {
	if(l == 0 && r == n-1) return 0;
	int &ret = dp[l][r][m];
	if(ret) return ret;
	ret = INT_MAX;
	int sum = (l ? wat[l-1] : 0) + wat[n-1] - wat[r], p = m ? pos[r] : pos[l];
	if(l) ret = min(ret, solve(l-1, r, 0) + (p-pos[l-1])*sum);
	if(r != n-1) ret = min(ret, solve(l, r+1, 1) + (pos[r+1]-p)*sum);
	return ret;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
	int m;
	cin >> n >> m;
	m--;
	for(int i=0; i<n; i++) {
		cin >> pos[i] >> wat[i];
		if(i) wat[i] += wat[i-1];
	}
	cout << solve(m, m, 0);
}
