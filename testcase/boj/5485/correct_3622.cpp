#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e6+2;
int m[MX], a[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> m[i];
	a[0] = m[0];
	int until = 0, bk = LLONG_MAX;
	for(int i=1; i<n+1; i++) {
		a[i] = m[i-1] * 2 - a[i-1];
		if(i&1) {
			if(a[i-1] > a[i]) {
				until = max(until, (a[i-1] - a[i]) / 2);
			}
		} else {
			bk = min(bk, (a[i] - a[i-1]) / 2);
		}
	}
	cout << max(bk - until +1, 0ll);
}
