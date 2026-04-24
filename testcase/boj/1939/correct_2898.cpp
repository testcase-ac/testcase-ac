#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); i++)

int n,m;
vector<vector<pair<int,int>>> adj;
int s,t;
bool ok(int maxw) {
	queue<int> que;
	vector<bool> seen(n);
	que.push(s);
	seen[s] = true;
	while(!que.empty()) {
		int q = que.front();
		if(q == t) return true;
		que.pop();
		for(auto pr: adj[q]) {
			if(maxw <= pr.second && !seen[pr.first]) {
				seen[pr.first] = true;
				que.push(pr.first);
			}
		}
	}
	return false;
}

int main() {
	cin >> n >> m;
	adj.resize(n);
	rep(i,m) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	cin >> s >> t;
	s--, t--;
	int l = 1, r = 1e9, mid;
	while(l < r) {
		mid = (l+r+1)/2;
		bool yes = ok(mid);
		if(yes)
			l = mid;
		else
			r = mid - 1;
	}
	cout << l << '\n';
}
