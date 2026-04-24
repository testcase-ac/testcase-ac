#include <bits/stdc++.h>
using namespace std;
#define int long long
struct pt {
	int m, p, r;
	bool operator<(pt& x) {
		return r*x.p < x.r*p;
	}
};
pt arr[51];
int dp[51][100001];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	// 1733
	int n, t;
	cin >> n >> t;
	for(int i=1; i<=n; i++) {
		cin >> arr[i].m;
	}
	for(int i=1; i<=n; i++) {
		cin >> arr[i].p;
	}
	for(int i=1; i<=n; i++) {
		cin >> arr[i].r;
	}
	sort(arr+1, arr+1+n);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=t; j++) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			if(j >= arr[i].r) {
				dp[i][j] = max(dp[i][j], dp[i-1][j-arr[i].r]+arr[i].m-(j*arr[i].p));
			}
		}
	}
	cout << dp[n][t];
}
