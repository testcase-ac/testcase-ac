#include <bits/stdc++.h>
using namespace std;

const int MX = 101;
int arr[MX], dp[MX][MX][6], n, k;
int f(int x, int y, int z) {
	if(dp[x][y][z] != -1)
		return dp[x][y][z];
	if(x == y)
		return max(0, k-z-1);
	else if(x > y)
		return 0;
	int res = k == z+1 ? f(x+1, y, 0) : f(x, y, z+1)+1;
	for(int i=x+1; i<=y; i++) {
		if(arr[x] == arr[i])
			res = min(res, f(x+1, i-1, 0)+f(i, y, min(z+1, k-1)));
	}
	dp[x][y][z] = res;
	return res;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k;
	for(int i=0; i<n; i++)
		cin >> arr[i];
	memset(dp, -1, sizeof dp);
	cout << f(0, n-1, 0);
}
