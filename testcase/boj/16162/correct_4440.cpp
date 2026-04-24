#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, a, d, ans = 0;
	cin >> n >> a >> d;
	while(n--) {
		int t;
		cin >> t;
		if(a == t) {
			ans++;
			a += d;
		}
	}
	cout << ans;
}
