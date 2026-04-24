#include <bits/stdc++.h>
using namespace std;
const int MX = 102;
int arr[MX], cost[MX][MX], dp[MX][MX], n;
int f(int a, int b) {
	if(dp[a][b] != -1)
		return dp[a][b];
	if(a == n)
		return b ? 9999 : 0;
	else if(b <= 0)
		return 9999;
	int &ret = dp[a][b];
	ret = 9999;
	for(int i=a; i<n; i++) {
		ret = min(ret, cost[a][i]+f(i+1, b-1));
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	memset(dp, -1, sizeof dp);
	for(int i=0; i<n; i++) {
		int p = 0;
		for(int j=i; j<n; j++) {
			if(arr[j] != j-i)
				p++;
			cost[i][j] = p;
		}
	}
	for(int i=1; i<=n; i++) {
		cout << f(0, i) << '\n';
	}
}
