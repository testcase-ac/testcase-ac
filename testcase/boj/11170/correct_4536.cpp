#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6+1;
int dp[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	dp[0] = 1;
	for(int i=10; i<MX; i++) {
		dp[i] = (i % 10 == 0) + dp[i/10];
	}
	int t;
	cin >> t;
	while(t--) {
		int a, b;
		cin >> a >> b;
		cout << accumulate(dp+a, dp+b+1, 0) << '\n';
	}
}
