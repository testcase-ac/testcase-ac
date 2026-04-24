#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

#define MAXN 100000
int dp[MAXN+1];

inline int square(int i) {return i*i;}
int rec(int n) {
	if(n == 1) return 1;
	int ret = INT_MAX;
	for(int i=1; square(i) <= n; i++) {

	}
}

int main() {
	int N;
	cin >> N;
	for(int n=1; n<=N; n++) {
		int ans = INT_MAX;
		for(int i=1; square(i)<=n;i++) {
			ans = min(ans, dp[n-square(i)]+1);
		}
		dp[n] = ans;
	}
	cout << dp[N];
}
