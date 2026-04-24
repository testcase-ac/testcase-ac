#include <bits/stdc++.h>
using namespace std;
bool grid[101][101];
int n, m, k;
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int dfs(int r, int c) {
	int ret = 1;
	grid[r][c] = false;
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(1 <= tr && tr <= n && 1 <= tc && tc <= m && grid[tr][tc]) {
			ret += dfs(tr, tc);
		}
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> k;
	while(k--) {
		int a, b;
		cin >> a >> b;
		grid[a][b] = 1;
	}
	int ans = 0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			if(grid[i][j]) {
				ans = max(ans, dfs(i, j));
			}
		}
	}
	cout << ans;
}
