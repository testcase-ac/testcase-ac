#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
const int MX = 100;
double dp[MX], dpnxt[MX], arr[MX][MX];
string names[MX];
void solve() {
	int n, k;
	cin >> n >> k;
	int st = -1;
	for(int i=0; i<n; i++) {
		cin >> names[i];
		if(names[i] == "ICN")
			st = i;
	}
	for(int i=0; i<n; i++) {
		double sum = 0;
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
			sum += arr[i][j];
		}
		if(sum > 0) {
			for(int j=0; j<n; j++) {
				arr[i][j] /= sum;
			}
		}
	}
	memset(dp, 0, sizeof dp);
	dp[st] = 1;
	for(int t=0; t<k; t++) {
		double mmx = 0;
		for(int i=0; i<n; i++) {
			double mx = 0;
			for(int j=0; j<n; j++) {
				mx = max(mx, dp[j]*arr[j][i]);
			}
			dpnxt[i] = mx;
			mmx = max(mmx, mx);
		}
		if(mmx < 0) {
			for(int i=0; i<n; i++) {
				dpnxt[i] *= (1<<20);
			}
		}
		memcpy(dp, dpnxt, sizeof dp);
	}
	int mxi = max_element(dp, dp+n) - dp;
	cout << names[mxi] << '\n';
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		solve();
}
