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

int dp[31][2][1001], arr[1001];
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int t, w;
	cin >> t >> w;
	for(int i=1;i<=t;i++){
		cin >> arr[i];
		arr[i]--;
	}
	// init with no move
	for(int i=1; i<=t; i++) {
		if(arr[i] == 0)
			dp[0][0][i] = dp[0][0][i-1] + 1;
		else
			dp[0][0][i] = dp[0][0][i-1];
	}
	for(int i=1;i<=w;i++) {
		for(int j=1;j<=t;j++) {
			rep(k,2) {
				dp[i][k][j] = max(dp[i-1][k^1][j-1], dp[i][k][j-1]);
				if(arr[j] == k)
					dp[i][k][j]++;
			}
		}
	}
	int ans = 0;
	rep(i, 2) {
		rep(j, 31) {
			ans = max(ans, dp[j][i][t]);  // JIT?
		}
	}
	cout << ans;
}
