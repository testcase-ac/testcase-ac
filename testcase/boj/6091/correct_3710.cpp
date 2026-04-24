#include <bits/stdc++.h>
using namespace std;
#define int long long
struct info {
	int i, j, w;
};
int par[2000];
int f(int i){return par[i] == i ? i : par[i] = f(par[i]);}
vector<int> adj[2000];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++)
		par[i] = i;
	vector<info> v;
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++) {
			v.push_back({i,j,0});
			cin >> v.back().w;
		}
	}
	sort(v.begin(), v.end(), [](auto a, auto b){return a.w < b.w;});
	for(auto [i, j, w]: v) {
		if(f(i) == f(j)) continue;
		adj[i].push_back(j);
		adj[j].push_back(i);
		par[f(i)] = f(j);
	}
	for(int i=1; i<=n; i++) {
		cout << adj[i].size() << ' ';
		sort(adj[i].begin(), adj[i].end());
		for(int t: adj[i])
			cout << t << ' ';
		cout << '\n';
	}
}
