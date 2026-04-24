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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	ll dp[16][16];
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			if(i == 0 || j == 0) dp[i][j] = 1;
			else dp[i][j] = dp[i][j-1] + dp[i-1][j];
		}
	}
	int n, m, k;
	cin >> n >> m >> k;
	if(k == 0) return !(cout << dp[n-1][m-1]);
	k--;
	int kr = k/m, kc = k%m;
	cout << (dp[kr][kc] * dp[n-kr-1][m-kc-1]);
}
