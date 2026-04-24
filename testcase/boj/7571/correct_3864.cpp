#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5;
int x[MX], y[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);	
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		cin >> x[i] >> y[i];
	}
	sort(x, x+m);
	sort(y, y+m);
	int ans = 0;
	for(int i=0; i<m; i++) {
		ans += abs(x[i]-x[m/2]) + abs(y[i]-y[m/2]);
	}
	cout << ans;
}
