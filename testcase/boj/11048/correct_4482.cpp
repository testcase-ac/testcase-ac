#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 1000
int arr[MAXN][MAXN], dp[MAXN][MAXN];

inline int max(int a, int b) {
	return (a > b ? a : b);
}

int main() {
    ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	rep(i, n) rep(j, m) cin >> arr[i][j];
	dp[n-1][m-1] = arr[n-1][m-1];
	for(int j=m-2;j>=0;j--)
		dp[n-1][j] = dp[n-1][j+1] + arr[n-1][j];
	for(int i=n-2;i>=0;i--)
		dp[i][m-1] = dp[i+1][m-1] + arr[i][m-1];
	for(int i=n-2;i>=0;i--) {
		for(int j=m-2;j>=0;j--) {
			dp[i][j] = max(dp[i+1][j], dp[i][j+1]) + arr[i][j];
		}
	}
	cout << dp[0][0];

}
