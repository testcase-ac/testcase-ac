#include <bits/stdc++.h>
using namespace std;
int a[20000], b[20000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		for(int i=0; i<n; i++) {
			cin >> a[i];
		}
		for(int i=0; i<m; i++) {
			cin >> b[i];
		}
		sort(a, a+n);
		sort(b, b+m);
		int j = 0, ans = 0;
		for(int i=0; i<n; i++) {
			while(j < m && b[j] < a[i]) j++;
			ans += j;
		}
		cout << ans << '\n';
	}
}
