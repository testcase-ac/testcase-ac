#include <bits/stdc++.h>
using namespace std;

const int MX = 100000;
int parent[MX], setsz[MX];
int find(int i) {return i == parent[i] ? i : parent[i] = find(parent[i]);}
void join(int i, int j) {
	if(i != j) {
		parent[j] = i;
		setsz[i] += setsz[j];
	}
}
vector<pair<int, int>> edges[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		parent[i] = i;
		setsz[i] = 1;
	}
	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[w].push_back({u-1,v-1});
	}
	int ans = 0;
	for(int c=1;c<=1000;c++) {
		for(auto pr: edges[c]) {
			int i = find(pr.first), j = find(pr.second);
			if(i != j) {
				join(i, j);
				if(setsz[i] == n)
					return !(cout << ans);
				ans += c;
			}
		}	
	}
}
