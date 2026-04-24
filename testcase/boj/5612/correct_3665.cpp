#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int ans = m;
	for(int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		m = m+a-b;
		if(m < 0) return !(cout << 0);
		ans = max(ans, m);
	}
	cout << ans;
}
