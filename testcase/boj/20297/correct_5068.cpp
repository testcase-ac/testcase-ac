#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> adj[100001];
int val[100001], dep[100001];
int ans = 1001412;
map<int, int> dfs(int i, int p, int d) {
	map<int, int> main_mp;
	for(auto a: adj[i]) {
		if(a == p) continue;
		auto mp = dfs(a, i, d+1);
		if(main_mp.size() < mp.size())
			swap(main_mp, mp);
		for(auto &pr: mp) {
			auto it = main_mp.find(pr.first);
			if(it != main_mp.end()) {
				ans = min(ans, (pr.second - d) + ((it->second) - d));
				it->second = min(it->second, pr.second);
			} else {
				main_mp[pr.first] = pr.second;
			}
		}
	}
	auto it = main_mp.find(val[i]);
	if(it != main_mp.end()) {
		ans = min(ans, (it->second) - d);
	}
	main_mp[val[i]] = d;
	return main_mp;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> val[i];
	}
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1, 0, 1);
	cout << ans;
}
