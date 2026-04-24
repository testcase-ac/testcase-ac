#include <bits/stdc++.h>
using namespace std;

const int MX = 501;
int dp[MX][5001], arr[MX], acc;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t, n;
	cin >> t >> n;
	dp[0][0] = 1;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	reverse(arr+1, arr+n+1);
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=t; j++) {
			if(dp[i-1][j]) {
				if(j+arr[i] <= t)
					dp[i][j+arr[i]] = 1;
				if(acc-j+arr[i] <= t)
					dp[i][j] = 2;
			}
		}
		acc += arr[i];
	}
	int l = 0, r = 0, j = 0;
	while(!dp[n][j]) j++;
	for(int i=n; i; i--) {
		if(dp[i][j] == 1) {
			j -= arr[i];
			cout << l << ' ';
			l += arr[i];
		} else {
			cout << r << ' ';
			r += arr[i];
		}
	}
}
