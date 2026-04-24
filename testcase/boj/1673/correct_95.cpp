#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	while(!(cin >> n >> k).eof()) {
		int ans = n, dojang = n;
		while(dojang >= k) {
			ans += dojang / k;
			dojang = dojang % k + dojang / k;
		}
		cout << ans << '\n';
	}
}
