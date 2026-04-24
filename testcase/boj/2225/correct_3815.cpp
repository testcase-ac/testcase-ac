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

#define MAXN 200
#define MOD 1000000000
int dp[MAXN+1][MAXN+1]; //dp[n][k]: 숫자 n이 k개 숫자의 합으로 표현할 수 있는 경우의 수
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int N, K;
	cin >> N >> K;
	rep(i, K+1)
		dp[0][i] = 1;
	for(int n=1; n<=N; n++) {
		for(int k=1; k<=K; k++) {
			for(int i=0; i<=n; i++) {
				dp[n][k] += dp[n-i][k-1];
				dp[n][k] %= MOD;
			}
		}
	}
	/*
	rep(i, N+1) {
		rep(j, K+1) {
			cout << dp[i][j] << ' ';
		}
		cout << '\n';
	}
	*/
	cout << dp[N][K];

}
