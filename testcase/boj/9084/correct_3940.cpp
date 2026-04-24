#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n,m;
		cin >> n;
		int coin[n];
		rep(i, n) cin >> coin[i];
		cin >> m;
		int dp[n][m+1];
		set0(dp);
		for(int val=0; val<=m; val+=coin[0])
			dp[0][val] = 1;
		for(int i=1;i<n;i++) {
			for(int j=0; j<=m; j++) {
				dp[i][j] = dp[i-1][j];
				int val = j - coin[i];
				while(val >= 0) {
					dp[i][j] += dp[i-1][val];
					val -= coin[i];
				}
			}
		}
		cout << dp[n-1][m] << '\n';
	}
}
