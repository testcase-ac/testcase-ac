#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3002;
int a[MX], b[MX], dp[MX][MX][2], n, m, L;
int cost(int x, int y, int t) { // mid / edge
	int c = (a[x]-b[y]) * (a[x]-b[y]) + L*L;
	return !t ? c * (n+m-1) : c * (x+y-1) * (n+m - (x+y-1));
}
int f(int x, int y, int t) {
	if(x == 1 && y == 1)
		return cost(1, 1, 0);
	else if (x < 1 || y < 1)
		return (int)1e18l;
	int &ret = dp[x][y][t];
	if(ret != -1)
		return ret;
	if(t == 0) {
		ret = min(f(x-1, y, 0) + cost(x, y, 0), f(x, y-1, 1) + cost(x, y, 1));
	} else {
		ret = min(f(x, y-1, 1) + cost(x, y, 0), f(x-1, y, 0) + cost(x, y, 1));
	}
	//printf("dp %d, %d, %d = %d\n", x, y, t);
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> L;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}
	for(int i=1; i<=m; i++) {
		cin >> b[i];
	}
	memset(dp, -1, sizeof dp);
	cout << min(f(n, m, 0), f(n, m, 1));
}
