#include <bits/stdc++.h>
using namespace std;

int dp[101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, add = 1;
	cin >> n;
	dp[1] = 2;
	for(int i=2; i<=n; i++) {
		if(i%2 == 0) add++;
		dp[i] = dp[i-1] + add;
	}
	cout << dp[n];
}
