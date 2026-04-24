#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 15746
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> dp(n+1);
	dp[1] = 1;
	dp[2] = 2;
	for(int i=3; i<=n; i++) {
		dp[i] = (dp[i-1] + dp[i-2]) % MOD;
	}
	cout << dp[n];

}
