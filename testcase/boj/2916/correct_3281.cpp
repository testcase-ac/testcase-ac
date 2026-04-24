#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int a[n], g;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	g = 360;
	for(int i=0; i<n; i++) {
		g = __gcd(g, a[i]);
	}
	while(m--) {
		int t;
		cin >> t;
		cout << (t % g ? "NO\n" : "YES\n");
	}
}
