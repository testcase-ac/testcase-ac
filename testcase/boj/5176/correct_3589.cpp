#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int p, m;
		cin >> p >> m;
		bool full[m] = {};
		int ans = 0;
		while(p--) {
			int t;
			cin >> t;
			t--;
			if(full[t])
				ans++;
			else
				full[t] = true;
		}
		cout << ans << '\n';
	}
}
