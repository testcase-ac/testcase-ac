#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
#define int long long
vector<pair<int, int>> adj[MX];
pair<int, int> dp[18][MX]; // node, weight
int h[MX];
void dfs(int i, int p) {
	for(auto pr: adj[i]) {
		if(pr.first == p) continue;
		dp[0][pr.first] = {i, pr.second};
		h[pr.first] = h[i]+1;
		dfs(pr.first, i);
	}
}
void lca(int u, int v, int& w, int& uh, int& vh) {
	w = uh = vh = 0;
	bool swp = 0;
	if(h[u] > h[v]) {
		swp = 1;
		swap(u, v);
	}
	int diff = h[v] - h[u];
	vh += diff;
	for(int i=0; i<18; i++) {
		if(diff&(1<<i)) {
			w += dp[i][v].second;
			v = dp[i][v].first;
		}
	}
	if(u != v) {
		for(int i=17; i>=0; i--) {
			if(dp[i][u].first != dp[i][v].first) {
				uh += (1<<i);
				vh += (1<<i);
				w += dp[i][u].second + dp[i][v].second;
				u = dp[i][u].first;
				v = dp[i][v].first;
			}
		}
		uh++;
		vh++;
		w += dp[0][u].second + dp[0][v].second;
	}
	if(swp)
		swap(uh, vh);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	dfs(1, 0);
	for(int t=1; t<18; t++) {
		for(int i=1; i<=n; i++) {
			dp[t][i] = {dp[t-1][dp[t-1][i].first].first, dp[t-1][i].second + dp[t-1][dp[t-1][i].first].second};
		}
	}
	int q;
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		int w, uh, vh;
		if(t == 1) {
			int u, v;
			cin >> u >> v;
			lca(u, v, w, uh, vh);
			cout << w << '\n';
		} else {
			int u, v, k;
			cin >> u >> v >> k;
			lca(u, v, w, uh, vh);
			if(uh+1 >= k) {
				k--;
				for(int i=0; i<18; i++) {
					if(k&(1<<i))
						u = dp[i][u].first;
				}
				cout << u << '\n';
			} else {
				int diff = uh+vh+1-k;
				for(int i=0; i<18; i++) {
					if(diff&(1<<i))
						v = dp[i][v].first;
				}
				cout << v << '\n';
			}
		}
	}
}
