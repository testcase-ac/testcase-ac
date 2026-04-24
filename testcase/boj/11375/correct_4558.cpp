#include <bits/stdc++.h>
using namespace std;
const int MX = 1001;
vector<int> adj[MX];
int match[MX];
bool seen[MX];
bool dfs(int i) {
	if(seen[i]) return 0;
	seen[i] = 1;
	for(int a: adj[i]) {
		if(!match[a] || dfs(match[a])) {
			match[a] = i;
			return 1;
		}
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		int c, t;
		cin >> c;
		while(c--) {
			cin >> t;
			adj[i].push_back(t);
		}
	}
	int ans = 0;
	for(int i=1; i<=n; i++) {
		memset(seen, 0, sizeof seen);
		if(dfs(i))
			ans++;
	}
	cout << ans;
}
