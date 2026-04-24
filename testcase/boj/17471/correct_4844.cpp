#include <bits/stdc++.h>
using namespace std;

int cnt[11], which[11], n, seen[11], ans = INT_MAX;
vector<int> adj[11];
int dfs(int i) {
	if(seen[i])
		return 0;
	seen[i] = 1;
	int ret = cnt[i];
	for(int a: adj[i]) {
		if(which[i] == which[a])
			ret += dfs(a);
	}
	return ret;
}
void f(int t) {
	if(t == n+1) {
		vector<int> v;
		memset(seen, 0, sizeof seen);
		for(int i=1; i<=n; i++) {
			if(!seen[i]) {
				v.push_back(dfs(i));
			}
		}
		if(v.size() == 2) {
			ans = min(ans, abs(v[0]-v[1]));
		}
		return;
	}
	which[t] = 0;
	f(t+1);
	which[t] = 1;
	f(t+1);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> cnt[i];
	}
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t;
		while(t--) {
			int s;
			cin >> s;
			adj[i].push_back(s);
		}
	}
	f(1);
	cout << (ans == INT_MAX ? -1 : ans);
}
