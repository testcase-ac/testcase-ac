#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

#define MOD 1000000007
using namespace std;

struct customCompare {
	bool operator() (const pair<int,int> &lhs, const pair<int,int> &rhs) const {
		return lhs.second > rhs.second;
	}
};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int V, E, u, v, w;
	cin >> V >> E;
	vector<vector<pair<int,int>>> adj(V);
	vector<bool> selected(V);
	priority_queue<pair<int,int>, vector<pair<int,int>>, customCompare> que;  // destination of path, weight of path
	ll ans = 0;
	rep(i, E) {
		cin >> u >> v >> w;
		u--; v--;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	selected[0] = true;
	for(auto pr: adj[0]) {
		que.push(pr);
	}
	while(!que.empty()) {
		auto pr = que.top();
		que.pop();
		if(!selected[pr.first]) {
			ans += (ll)pr.second;
			//printf("pr.first=%d, pr.second=%d. ans is now %d\n", pr.first, pr.second, ans);
			selected[pr.first] = true;
			for(auto nextpr: adj[pr.first]) {
				if(!selected[nextpr.first])
					que.push(nextpr);
			}
		}
	}
	cout << ans;

}
