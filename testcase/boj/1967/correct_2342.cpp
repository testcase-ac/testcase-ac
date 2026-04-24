#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
vector<vector<pair<int,int>>> adj;
struct cc {bool operator() (const pair<int,int> &lhs, const pair<int,int> &rhs) const { return lhs.first > rhs.first;}};

pair<int,int> findLastNode(int src) {  // its cost, its index
	pair<int,int> ret;
	priority_queue<pair<int,int>, vector<pair<int,int>>, cc> pq; 
	pq.emplace(0, src);
	vector<bool> visited(sz(adj));
	visited[src] = true;
	int lastpop, lastcost;
	while(!pq.empty()) {
		auto pr = pq.top();
		pq.pop();
		lastpop = pr.second;
		lastcost = pr.first;
		for(auto v: adj[lastpop]) {
			if(!visited[v.second]) {
				visited[v.second] = true;
				pq.emplace(pr.first+v.first, v.second);
			}
		}
	}
	ret.first = lastcost;
	ret.second = lastpop;
	return ret;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	adj.resize(n);
	rep(i, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].emplace_back(w, v);
		adj[v].emplace_back(w, u);
	}
	auto pr = findLastNode(0);
	//printf("farthest from 0 is %d, at dist=%d.\n", pr.second, pr.first);
	auto pr2 = findLastNode(pr.second);
	//printf("farthest from %d is %d, at dist=%d.\n", pr.second, pr2.second, pr2.first);
	cout << pr2.first;
}
