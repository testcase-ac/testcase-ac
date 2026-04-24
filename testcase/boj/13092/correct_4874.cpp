#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[2][1001][1001], opt[2][1001][1001], arr[1001];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, K;
	cin >> n >> K;
	for(int i=0; i<n; i++)
		cin >> arr[i];
	sort(arr, arr+n);
	memset(dp[0], 0x3f, sizeof dp);
	for(int i=0; i<n; i++)
		dp[0][i][i] = 0;
	for(int k=1; k<=K; k++) {
		int c = k&1, p = c^1;
		for(int i=0; i<n; i++) {
			dp[c][i][i] = 0;
			opt[c][i][i] = i;
		}
		for(int d=1; d<n; d++) {
			for(int i=0, j=i+d; j<n; i++, j++) {
				dp[c][i][j] = LLONG_MAX;
				for(int l=opt[c][i][j-1]; l<=opt[c][i+1][j]; l++) {
					int v = dp[p][i][l] + dp[p][l+1][j] + arr[j] - arr[l];
					if(v < dp[c][i][j]) {
						dp[c][i][j] = v;
						opt[c][i][j] = l;
					}
				}
			}
		}
	}
	cout << dp[K&1][0][n-1];
}
