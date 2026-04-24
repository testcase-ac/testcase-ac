#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, n, l;
	cin >> r >> n;
	l = r;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		if(t < l) {
			l++;
			r++;
		} else if(t == l) {
			r++;
		} else if(t <= r) {
			l = t;
			r++;
		}
	}
	cout << l << ' ' << r;
}
