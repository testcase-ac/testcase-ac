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
#define MAXN 5000
int n;
int arr[MAXN];
int dp[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	rep(i, n) cin >> arr[i];
	for(int diff=1; diff<n; diff++) {
		for(int i=0; i+diff<n; i++) {
			if(arr[i] == arr[i+diff])
				dp[i][i+diff] = dp[i+1][i+diff-1];
			else
				dp[i][i+diff] = min(dp[i][i+diff-1], dp[i+1][i+diff])+1;
		}
	}
	cout << dp[0][n-1];
}
