#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
const int MX = 2e4+2;
int k, n;
double a[MX], one;
int segnum(double st, double num) {
	if(num >= st) {
		return (num - st) / one;
	} else {
		num += 360;
		return (num - st) / one;
	}
}
int solve() {
	int ans = INT_MAX;
	for(int t=0; t<n; t++) {
		int cntmi = INT_MAX, cntmx = 0;
		double st = a[t];
		int lstsg = -1;
		for(int i=t, j=t; i<n+t; i=j) {
			while(j < n+t && segnum(st, a[i]) == segnum(st, a[j]))
				j++;
			if(segnum(st, a[i]) > lstsg + 1) {
				cntmi = 0;
			}
			lstsg = segnum(st, a[i]);
			cntmi = min(cntmi, j-i);
			cntmx = max(cntmx, j-i);
		}
		if(lstsg != k-1)
			cntmi = 0;
		//printf("at i=%d, cntmi = %d, cntmx = %d\n", t, cntmi, cntmx);
		ans = min(ans, cntmx - cntmi);
	}
	return ans;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k;
	one = 360.0 / k;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a, a+n);
	memcpy(a+n, a, sizeof(double)*n);
	int ans = solve();
	// for(int i=0; i<2*n; i++) {
	// 	a[i] = 360 - a[i];
	// }
	// reverse(a, a+n);
	// reverse(a+n, a+n+n);
	// ans = min(ans, solve());
	cout << ans;
}
