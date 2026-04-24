#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t, c = 0, n, ans = 0;
	cin >> n;
	while(n--) {
		cin >> t;
		if(t == c) {
			ans++;
			c = (c+1)%3;
		}
	}
	cout << ans;
}
