#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	int arr[n][m], dp[n][m]; set0(dp);
	string str;
	rep(r, n) {
		cin >> str;
		rep(c, m) {
			arr[r][c] = str[c] - '0';
		}
	}
	int ans = 0;
	rep(r, n) ans = max(ans, dp[r][0] = arr[r][0]);
	rep(c, m) ans = max(ans, dp[0][c] = arr[0][c]);
	for(int r=1; r<n; r++) {
		for(int c=1; c<m; c++) {
			if(arr[r][c]) {
				int m = min(min(dp[r-1][c], dp[r][c-1]), dp[r-1][c-1]);
				dp[r][c] = m+1;
				ans = max(dp[r][c], ans);
			}
		}
	}
	cout << (ans*ans);
}
