#include <bits/stdc++.h>
using namespace std;
int mark[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int t;
		cin >> t;
		for(int i=t; i<=n; i+=t) {
			mark[i] = 1;
		}
	}
	int ans = 0;
	for(int i=1; i<=n; i++) {
		if(mark[i])
			ans += i;
	}
	cout << ans;
}
