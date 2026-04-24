#include <bits/stdc++.h>
using namespace std;
#define int long long
map<int, vector<int>> adj;
set<int> seen;
int mx, ecnt, ncnt, sum;
void dfs(int i) {
	if(seen.count(i)) return;
	seen.insert(i);
	sum += i * ((int)adj[i].size() - 1);
	ncnt++;
	ecnt += adj[i].size();
	mx = max(mx, i);
	for(int a: adj[i]) {
		dfs(a);
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int ans = 0;
	for(auto [k, _]: adj) {
		if(!seen.count(k)) {
			mx = ncnt = ecnt = sum = 0;
			dfs(k);
			ecnt /= 2;
			assert(ncnt == ecnt || ncnt == ecnt+1);
			ans += sum;
			if(ncnt == ecnt + 1)
				ans += mx;
		}
	}
	cout << ans;
}
