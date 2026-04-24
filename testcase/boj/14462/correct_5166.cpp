#include <bits/stdc++.h>
using namespace std;
int a[1000], b[1000], dp[1000][1000], n;
int f(int x, int y) {
	if(x >= n || y >= n)
		return 0;
	if(dp[x][y] != -1)
		return dp[x][y];
	int &ret = dp[x][y];
	ret = f(x+1, y);
	for(int j=y; j<n; j++) {
		if(abs(a[x]-b[j]) <= 4) {
			ret = max(ret, 1+f(x+1, j+1));
		}
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	memset(dp, -1, sizeof dp);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<n; i++) {
		cin >> b[i];
	}
	cout << f(0,0);
}
