#include <bits/stdc++.h>
using namespace std;

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	n *= 2;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	int s = INT_MAX;
	for(int i=0; i<n; i++) {
		s = min(v[i]+v[n-1-i], s);
	}
	cout << s;
}
