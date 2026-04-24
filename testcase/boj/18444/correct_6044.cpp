#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 251;
int arr[MX], acc[MX], n, M, L, dp[MX][MX], dopt[MX][MX];
vector<int> ansv;
int cost(int l, int r) {
	if(l == r)
		return 0;
	int mid = (l+r)/2;
	return (acc[r] - acc[mid-1]) - arr[mid] * (r - mid + 1) + arr[mid] * (mid - l) - (acc[mid-1] - acc[l-1]);
}
void f(int i, int l, int r, int optl, int optr) {
	if(l > r)
		return;
	int m = (l+r)/2;
	int opt = optl;
	for(int j=optl; j<=min(optr, m); j++) {
		int c = dp[i-1][j-1] + cost(j, m);
		if(c < dp[i][m]) {
			dp[i][m] = c;
			opt = j;
		}
	}
	dopt[i][m] = opt;
	f(i, l, m-1, optl, opt);
	f(i, m+1, r, opt, optr);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> M >> L;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	int ans = LLONG_MAX;
	for(int i=0; i<n; i++) {
		rotate(arr+1, arr+2, arr+n+1);
		arr[n] += L;
		memset(dp, 0x3f, sizeof dp);
		dp[0][0] = 0;
		for(int j=1; j<=n; j++)
			acc[j] = acc[j-1] + arr[j];
		for(int j=1; j<=M; j++) {
			f(j, 1, n, 1, n);
		}
		if(dp[M][n] < ans) {
			ans = dp[M][n];
			ansv.clear();
			int ci = M, cj = n;
			while(ci) {
				int o = dopt[ci][cj], ind = (o+cj)/2;
				ansv.push_back(arr[ind]);
				if(arr[ind] >= L) {
					ansv.back() -= L;
				}
				ci--;
				cj = o-1;
			}
		}
	}
	sort(ansv.begin(), ansv.end());
	cout << ans << '\n';
	for(int t: ansv)
		cout << t << ' ';
}
