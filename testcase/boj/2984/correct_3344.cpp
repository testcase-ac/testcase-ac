#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MX = 1e5+1;
int a[MX], b[MX];
ll dp[MX];
void check(int i, vector<int> perm) {
	if(i - (int)perm.size() < 0) return;
	ll v = 0;
	for(int j=0; j<perm.size(); j++) {
		int diff = abs(a[i-j] - b[i-perm[j]]);
		if(!diff) return;
		v += diff;
	}
	dp[i] = min(dp[i], dp[i-perm.size()]+v);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i] >> b[i];
	}
	sort(a+1, a+n+1);
	sort(b+1, b+n+1);
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for(int i=1; i<=n; i++) {
		check(i, {0});
		check(i, {1, 0});
		check(i, {2, 1, 0});
		check(i, {2, 0, 1});
		check(i, {1, 2, 0});
		check(i, {0, 2, 1});
	}
	cout << dp[n];
}
