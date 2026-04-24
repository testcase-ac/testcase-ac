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
	int n;
	cin >> n;
	ll dp[n][21], arr[n+1];
	set0(dp);
	rep(i,n) cin >> arr[i+1];
	dp[1][arr[1]] = 1;
	for(int i=2;i<n;i++) {
		for(int j=0;j<=20;j++) {
			if(j+arr[i] <= 20)
				dp[i][j+arr[i]] += dp[i-1][j];
			if(j-arr[i] >= 0)
				dp[i][j-arr[i]] += dp[i-1][j];
		}
	}
	cout << dp[n-1][arr[n]];
}
