#include <bits/stdc++.h>
using namespace std;
const int MX = 301;
int arr[MX][MX], dp[MX][MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=n-1; i>=0; i--) {
		for(int j=m-1; j>=0; j--) {
			dp[i][j] = arr[i][j]+max(dp[i+1][j], dp[i][j+1]);
		}
	}
	cout << dp[0][0];
}
