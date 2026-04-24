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
#define MAXN 500
int arr[MAXN][MAXN];
int dp[MAXN][MAXN]; // 0:unknown >0: reachable -1:not reachable
int m, n;

int dfs(int i, int j) {
	if((i == m-1) && (j == n-1)) {
		return 1;
	}
	int val = arr[i][j];
	int cnt = 0;
	if(i-1>=0 && val > arr[i-1][j]) {
		if(dp[i-1][j] == 0) cnt += dfs(i-1,j);
		else if(dp[i-1][j] > 0) cnt += dp[i-1][j];
	}
	if(i+1<m && val > arr[i+1][j]) {
		if(dp[i+1][j] == 0) cnt += dfs(i+1,j);
		else if(dp[i+1][j] > 0) cnt += dp[i+1][j];
	}
	if(j-1>=0 && val > arr[i][j-1]) {
		if(dp[i][j-1] == 0) cnt += dfs(i, j-1);
		else if(dp[i][j-1] > 0) cnt += dp[i][j-1];
	}
	if(j+1<n && val > arr[i][j+1]) {
		if(dp[i][j+1] == 0) cnt += dfs(i, j+1);
		else if(dp[i][j+1] > 0) cnt += dp[i][j+1]; 
	}
	if(cnt) dp[i][j] = cnt;
	else dp[i][j] = -1;
	return cnt;
}

int main() {
	cin >> m >> n;
	rep(i, m) {
		rep(j, n){
			cin >> arr[i][j];
		}
	}
	dfs(0,0);
	cout << (dp[0][0] > 0 ? dp[0][0] : 0);

}
