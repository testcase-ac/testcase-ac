#include <bits/stdc++.h>
using namespace std;

int arr[200], dp[200][200], n;
/*
dp[i][j]: the maximum pt difference achievable by last player, after [i,j] range is over.
*/
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		arr[i] &= 1;
		arr[i+n] = arr[i];
	}
	for(int i=0; i<n; i++) {
		dp[i][i] = dp[i+n][i+n] = arr[i];
	}
	for(int d=1; d<n; d++) {
		for(int l=0; l+d<2*n; l++) {
			int r = l+d;
			dp[l][r] = max(dp[l][l] - dp[l+1][r], dp[r][r] - dp[l][r-1]);
		}
	}
	int cnt = 0;
	for(int i=0; i<n; i++) {
		if(dp[i][i] - dp[i+1][i+n-1] > 0) {
			cnt++;
		}
	}
	cout << cnt;
}
