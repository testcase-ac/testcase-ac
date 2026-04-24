#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
	int x, y;
	int dist(point i) {
		return (x-i.x)*(x-i.x)+(y-i.y)*(y-i.y);
	}
};
const int MX = 1e3+2, INF = LLONG_MAX/2;
point a[MX], b[MX];
int dp[MX][MX][2], n, m;
int f(int i, int j, int p) {
	if(dp[i][j][p] != -1)
		return dp[i][j][p];
	if(i > n || j > m)
		return INF;
	if(i == n && j < m)
		return INF;
	if(i == n && j == m)
		return 0;
	int &ret = dp[i][j][p];
	point cur = p ? b[j-1] : a[i-1];
	ret = min(f(i+1, j, 0)+a[i].dist(cur), f(i, j+1, 1)+b[j].dist(cur));
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	for(int i=0; i<m; i++) {
		cin >> b[i].x >> b[i].y;
	}
	memset(dp, -1, sizeof dp);
	cout << f(1, 0, 0);
}
