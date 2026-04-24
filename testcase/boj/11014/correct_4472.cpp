#include <bits/stdc++.h>
using namespace std;
struct biparite {
	int n, m;
	vector<int> match, seen;
	vector<vector<int>> adj;
	biparite(int _n, int _m) {
		n = _n, m = _m;
		match.resize(m, -1);
		seen.resize(n);
		adj.resize(n);
	}
	void addedge(int u, int v) {
		adj[u].push_back(v);
	}
	bool dfs(int i) {
		if(seen[i])
			return 0;
		seen[i] = 1;
		for(int a: adj[i]) {
			if(match[a] == -1 || dfs(match[a])) {
				match[a] = i;
				return 1;
			}
		}
		return 0;
	}
	int solve() {
		int ans = 0;
		for(int i=0; i<n; i++) {
			fill(seen.begin(), seen.end(), 0);
			if(dfs(i))
				ans++;
		}
		return ans;
	}
};
char arr[80][81];
int num[80][81];
int r, c;
int solve() {
	cin >> r >> c;
	memset(num, -1, sizeof num);
	int nxt[2] = {0,0};
	for(int i=0; i<r; i++) {
		cin >> arr[i];
		for(int j=0; j<c; j++) {
			if(arr[i][j] == '.')
				num[i][j] = nxt[j&1]++;
		}
	}
	biparite bip(nxt[0], nxt[1]);
	auto addedge = [&](int i, int j, int x, int y) {
		if(!(0 <= i && i < r && 0 <= j && j < c && 0 <= x && x < r && 0 <= y && y < c))
			return;
		if(num[i][j] == -1 || num[x][y] == -1)
			return;
		//printf("edge added: %d->%d\n", num[i][j], num[x][y]);
		bip.addedge(num[i][j], num[x][y]);
	};
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j+=2) {
			if(arr[i][j] == 'x')
				continue;
			addedge(i, j, i, j-1);
			addedge(i, j, i, j+1);
			addedge(i, j, i-1, j-1);
			addedge(i, j, i-1, j+1);
			addedge(i, j, i+1, j-1);
			addedge(i, j, i+1, j+1);
		}
	}
	return nxt[0]+nxt[1]-bip.solve();
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		cout << solve() << '\n';
}
