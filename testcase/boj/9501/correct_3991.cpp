#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, d, ans = 0;
		cin >> n >> d;
		for(int i=0; i<n; i++) {
			int v, f, c;
			cin >> v >> f >> c;
			ans += (v*((double)f/c) >= d);
		}
		cout << ans << '\n';
	}
}
