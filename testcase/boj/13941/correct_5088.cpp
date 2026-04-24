#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[20][20], dp[1<<20], n;
int f(int bm) {
	int &r = dp[bm];
	if(r != -1)
		return r;
	if(!bm)
		return 0;
	r = INT_MAX;
	for(int i=0; i<n; i++) {
		if((1<<i) & bm) {
			int t = f(bm ^ (1<<i)), mn = INT_MAX;
			for(int j=0; j<n; j++) {
				if(!((1<<j) & bm)) {
					mn = min(mn, arr[i][j]);
				}
			}
			r = min(r, t+mn);
		}
	}
	return r;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dp, -1, sizeof dp);
	int k;
	cin >> n >> k;	
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	int ans = INT_MAX;
	for(int i=0; i<(1<<n); i++) {
		if(__builtin_popcountll(i) == n-k) {
			ans = min(ans, f(i));
		}
	}
	cout << ans;
}
