#include <bits/stdc++.h>
using namespace std;
const int MX = 2e7+2;
int cost[MX], dp[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, s;
	cin >> n >> s;
	for(int i=0; i<n; i++) {
		int h, c;
		cin >> h >> c;
		cost[h] = max(cost[h], c);
	}
	for(int i=s; i<MX; i++) {
		dp[i] = dp[i-1];
		if(!cost[i]) continue;
		dp[i] = max(dp[i], dp[i-s]+cost[i]);
	}
	cout << dp[MX-1];
}
