#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;

int dp[101][10001], K[101], S[101];

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, t;
	cin >> n >> t;
	rep(i, n) cin >> K[i+1] >> S[i+1];
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=t; j++) {
			dp[i][j] = dp[i-1][j];
			if(j-K[i] >= 0)
				dp[i][j] = max(dp[i][j], dp[i-1][j-K[i]]+S[i]);
		}
	}
	cout << dp[n][t];
}
