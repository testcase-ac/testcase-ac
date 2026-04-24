#include <bits/stdc++.h>
using namespace std;
int arr[100][100], l, r, di[] = {1,-1,0,0}, dj[] = {0,0,1,-1}, n;
bool seen[100][100];
bool dfs(int i, int j) {
	if(i == n-1 && j == n-1)
		return 1;
	seen[i][j] = 1;
	for(int k=0; k<4; k++) {
		int ti = i+di[k], tj = j+dj[k];
		if(!(0 <= ti && ti < n) || !(0 <= tj && tj < n) || seen[ti][tj] || !(l <= arr[ti][tj] && arr[ti][tj] <= r))
			continue;
		if(dfs(ti, tj))
			return 1;
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	l = 0, r = max(arr[0][0], arr[n-1][n-1]);
	int ans = 300;
	while(l <= arr[0][0] && r <= 200) {
		memset(seen, 0, sizeof seen);
		if(dfs(0,0)) {
			ans = min(ans, r-l);
			l++;
		}
		else r++;
	}
	cout << ans;
}
