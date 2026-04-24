#include <bits/stdc++.h>
using namespace std;
int cost[256];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string a, b;
	cin >> a >> b;
	for(int i: {'A', 'C', 'G', 'T'}) {
		int t;
		cin >> t;
		cost[i] = t;
	}
	int n = a.size(), m = b.size(), ans = 1e9;
	for(int i=0; i<n; i++) {
		int j = i, k = 0, tans = 0;
		while(j < n && k < m) {
			while(k < m && b[k] != a[j])
				tans += cost[b[k++]];
			j++, k++;
		}
		while(k < m) {
			tans += cost[b[k++]];
		}
		ans = min(ans, tans);
	}
	cout << ans;
}
