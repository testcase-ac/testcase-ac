#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, ans = 0;
		cin >> n;
		for(int i=0; i<n; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			ans += max({0,a,b,c});
		}
		cout << ans << '\n';
	}
}
