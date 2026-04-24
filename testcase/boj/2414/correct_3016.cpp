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
char arr[50][51];
int hnum[50][51], vnum[50][51];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	int r, c;
	int nxt = 0;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			while(j < m && arr[i][j] == '.') j++;
			if(j >= m) break;
			while(j < m && arr[i][j] == '*') hnum[i][j++] = nxt;
			nxt++;
		}
	}
	r = nxt;
	nxt = 0;
	for(int j=0; j<m; j++) {
		for(int i=0; i<n; i++) {
			while(i < n && arr[i][j] == '.') i++;
			if(i >= n) break;
			while(i < n && arr[i][j] == '*') vnum[i++][j] = nxt;
			nxt++;
		}
	}
	c = nxt;
	biparite bp(r, c);
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			if(arr[i][j] == '*')
				bp.addedge(hnum[i][j], vnum[i][j]);
		}
	}
	cout << bp.solve();
}
