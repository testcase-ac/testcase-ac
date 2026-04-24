#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

#define MAXN 100
ll arr[MAXN][MAXN], dp[MAXN][MAXN];
int n;

ll rec(int i, int j) {
	ll ret = 0;
	int dist = arr[i][j];
	if(dist == 0) {
		if(i == n-1 && j == n-1)
			return 1;
		else
			return 0;
	}
	if(i+dist < n) {
		if(dp[i+dist][j] == -1) {
			ret += rec(i+dist, j);
		} else {
			ret += dp[i+dist][j];
		}
	}
	if(j+dist < n) {
		if(dp[i][j+dist] == -1) {
			ret += rec(i, j+dist);
		} else {
			ret += dp[i][j+dist];
		}
	}
	dp[i][j] = ret;
	return ret;
}

int main() {
	cin >> n;
	rep(i, n) {
		rep(j, n) {
			cin >> arr[i][j];
			dp[i][j] = -1;
		}
	}
	cout << rec(0, 0);
}
