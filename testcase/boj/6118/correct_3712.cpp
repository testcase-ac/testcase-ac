#include <bits/stdc++.h>
using namespace std;
vector<int> adj[20001];
int seen[20001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	memset(seen, -1, sizeof seen);
	queue<int> que({1});
	seen[1] = 0;
	int t = 0;
	while(!que.empty()) {
		t++;
		int s = que.size();
		while(s--) {
			int q = que.front();
			que.pop();
			for(int a: adj[q]) {
				if(seen[a] == -1) {
					seen[a] = t;
					que.push(a);
				}
			}
		}
	}
	auto it = max_element(seen, seen+n+1);
	cout << it-seen << ' ' << *it << ' ' << count(seen, seen+n+1, *it);
}
