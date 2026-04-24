#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[31][31];
ll rec(int full, int half) {
	if(full == 0) return 1;
	if(dp[full][half]) return dp[full][half];
	ll r = rec(full-1,half+1);
	if(half) r += rec(full, half-1);
	dp[full][half] = r;
	return r;
}
int main() {
	int t;
	while(1) {
		cin >> t;
		if(!t) break;
		cout << rec(t,0) << '\n';
	}
}
