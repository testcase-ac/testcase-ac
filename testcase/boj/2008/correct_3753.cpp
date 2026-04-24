#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[502][101], line[502];
int n, m, a, b, X, Y;
int f(int x, int y) {
	if(x < 0)
		return y == a ? 0 : 0x3f3f3f3f;
	int &ret = dp[x][y];
	if(ret != -1)
		return ret;
	ret = 0x3f3f3f3f;
	for(int j=1; j<=n; j++) {
		
		if(x && (line[x-1] == j || line[x-1]+1 == j)) {
			int tj = line[x-1] == j ? j+1 : j-1;
			ret = min({ret, abs(tj-y)*Y + f(x-1, j), abs(j-y)*Y+X + f(x-1, j)});
		} else {
			ret = min(ret, abs(j-y)*Y + f(x-1, j));
		}
	}
	//printf("dp %d, %d calced to be %d\n", x, y, dp[x][y]);
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> a >> b >> X >> Y;
	for(int i=0; i<m; i++)
		cin >> line[i];
	memset(dp, -1, sizeof dp);
	cout << f(m, b);
}
