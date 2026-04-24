#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int a[m], ans[n+1] = {};
	for(int i=0; i<m; i++) {
		cin >> a[i];
	}
	for(int i=0; i<m; i++) {
		int b, c = 0;
		for(int j=1; j<=n; j++) {
			cin >> b;
			if(b == a[i])
				ans[j]++;
			else
				c++;
		}
		ans[a[i]] += c;
	}
	for(int i=1; i<=n; i++) {
		cout << ans[i] << '\n';
	}
}
