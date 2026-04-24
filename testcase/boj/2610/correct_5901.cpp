#include <bits/stdc++.h>
using namespace std;

vector<int> adj[101];
vector<vector<int>> cc;
bool seen[101];
int fardist[101];
void findcc(int i) {
	seen[i] = true;
	for(int a: adj[i]) {
		if(!seen[a]) {
			cc.back().push_back(a);
			findcc(a);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	while(k--) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=1; i<=n; i++) {
		if(!seen[i]) {
			cc.push_back({i});
			findcc(i);
		}
	}
	for(int i=1; i<=n; i++) {
		queue<int> que;
		que.push(i);
		memset(seen, 0, sizeof seen);
		seen[i] = true;
		int d = 0;
		while(!que.empty()) {
			int s = que.size();
			while(s--) {
				int q = que.front();
				que.pop();
				for(int a: adj[q]) {
					if(!seen[a]) {
						seen[a] = true;
						que.push(a);
					}
				}
			}
			d++;
		}
		fardist[i] = max(0, d-2);
	}
	cout << cc.size() << '\n';
	vector<int> ans;
	for(int i=0; i<cc.size(); i++) {
		int mind = 1e9, mini;
		for(int c: cc[i]) {
			if(fardist[c] < mind) {
				mind = fardist[c];
				mini = c;
			}
		}
		ans.push_back(mini);
	}
	sort(ans.begin(), ans.end());
	for(int a: ans) cout << a << '\n';
}
