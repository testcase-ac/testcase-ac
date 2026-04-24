#include <bits/stdc++.h>
using namespace std;
#define int long long
// int dp[100][100];
// int f(int a, int b) {
// 	if(!a)
// 		return 0;
// 	if(dp[a][b] != -1)
// 		return dp[a][b];
// 	int& ret = dp[a][b];
// 	ret = 0;
// 	for(int i=1; i<=min(b*2, a); i++) {
// 		if(!f(a-i, i)) {
// 			ret = 1;
// 			break;
// 		}
// 	}
// 	return ret;
// }
// int32_t main() {
// 	ios::sync_with_stdio(0);cin.tie(0);
// 	memset(dp, -1, sizeof dp);
// 	int n;
// 	cin >> n;
// 	for(int i=1; i<=n; i++) {
// 		if(!f(n-i, i))
// 			return !(cout << i);
// 	}
// }
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v = {1,2};
	while(v.back() < 1e16) {
		int s = v.size();
		v.push_back(v[s-2]+v[s-1]);
	}
	reverse(v.begin(), v.end());
	int N = n;
	while(n) {
		int t = *lower_bound(v.begin(), v.end(), n, greater<int>());
		if(t == n && t != N)
			return !(cout << t);
		n -= t;
	}
	cout << -1;
}
