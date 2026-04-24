#include <bits/stdc++.h>
using namespace std;

int dp[50][500001]; // using to i block, made two towers with difference j, the height of smaller tower is dp[i][j]
int a[50];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	memset(dp, -1, sizeof dp);
	dp[0][0] = 0;
	dp[0][a[0]] = 0;
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<=500000; j++) {
			if(dp[i][j] == -1) continue;
			dp[i+1][j+a[i+1]] = max(dp[i+1][j+a[i+1]], dp[i][j]);
			dp[i+1][abs(j-a[i+1])] = max(dp[i+1][abs(j-a[i+1])], dp[i][j]+min(a[i+1],j));
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
		}
	}
	if(!dp[n-1][0]) cout << -1;
	else cout << dp[n-1][0];
}
