#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int N, S, M;
	cin >> N >> S >> M;
	bool dp[N+1][M+1];
	set0(dp);
	dp[0][S] = 1;
	for(int i=1;i<=N;i++) {
		int n;
		cin >> n;
		rep(j, M+1) {
			if(dp[i-1][j]) {
				if(j+n<=M)
					dp[i][j+n] = 1;
				if(j-n>=0)
					dp[i][j-n] = 1;
			}
		}
	}
	for(int j=M;j>=0;j--) {
		if(dp[N][j])
			return !(cout << j);
	}
	cout << -1;
}
