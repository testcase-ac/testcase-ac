#include <bits/stdc++.h>
using namespace std;

int dp[1000001];

int main() {
	int T, inp;
	cin >> T;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 4;
	for(int i=4; i<=1000000; i++) {
		dp[i] = (int)(((long long)dp[i-1]+ dp[i-2] + dp[i-3]) % (int)(1e9+9));
	}
	while(T--) {
		cin >> inp;
		cout << dp[inp] << '\n';
	}
}
