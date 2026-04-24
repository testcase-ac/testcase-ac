#include <bits/stdc++.h>
using namespace std;
char arr[50][51];
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, n, m;
vector<int> adj[2500];
int seen[2500], dp[2500];
void dfs(int i) {
	assert(!seen[i]);
	seen[i] = 1;
	int ret = 1;
	for(int a: adj[i]) {
		if(seen[a] == 1) {
			cout << -1;
			exit(0);
		} else if(!seen[a])
			dfs(a);
		ret = max(ret, 1+dp[a]);
	}
	seen[i] = 2;
	dp[i] = ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dp, -1, sizeof dp);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		for(int j=0; j<m; j++) {
			if(arr[i][j] != 'H')
				arr[i][j] -= '0';
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			for(int t=0; t<4; t++) {
				if(arr[i][j] == 'H') continue;
				int tr = i+dr[t]*arr[i][j], tc = j+dc[t]*arr[i][j];
				if(tr < 0 || tr >= n || tc < 0 || tc >= m || arr[tr][tc] == 'H') continue;
				adj[i*m+j].push_back(tr*m+tc);
			}
		}
	}
	dfs(0);
	cout << dp[0];
}
