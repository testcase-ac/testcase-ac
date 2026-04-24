#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3005;
int a[MX], acc[MX], dp[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, trk, hel;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
		
	}
	cin >> trk >> hel;
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++) {
		acc[i] = acc[i-1] + a[i];
	}
	for(int i=1; i<=n; i++) {
		dp[i] = LLONG_MAX;
		for(int j=i; j>=1; j--) {
			int m = (i+j)/2;
			int d1 = acc[i] - acc[m]- (i-m) * a[m], d2 = (m-j) * a[m] - (acc[m-1] - acc[j-1]);
			int d = (d1 + d2) * trk;
			dp[i] = min({dp[i], dp[j-1]+d+hel, dp[j-1]+trk*(acc[i]-acc[j-1])});
		}
	}
	cout << dp[n];
}
