#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<double> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	double l = 0, r = 100000;
	for(int j=0; j<100; j++) {
		double m = (l+r)/2, cur = 0, mx = INT_MIN, tsum = 0;
		for(int i=0; i<n; i++) {
			double t = v[i] - m;
			tsum += t;
			if(i == 0 || i == n-1) continue;
			cur = cur+t;
			mx = max(cur, mx);
			cur = max(0.0, cur);
		}
		if(tsum - mx > 0) {
			l = m;
		} else {
			r = m;
		}
	}
	printf("%.3f\n", l);
}
