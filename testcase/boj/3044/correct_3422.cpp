#include <bits/stdc++.h>
using namespace std;
vector<int> adj[10000];
vector<int> ts;
bool seen[10000], reachable[10000], over[10000];
int indexof[10000], dp[10000];
const int MOD = 1000000000;
bool dfs(int i) {
	seen[i] = true;
	bool ret = i == 1;
	for(int a: adj[i]) {
		if(!seen[a])
			dfs(a);
		if(reachable[a]) ret = true;
	}
	ts.push_back(i);
	reachable[i] = ret;
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		adj[a-1].push_back(b-1);
	}
	dfs(0);
	reverse(ts.begin(), ts.end());
	memset(indexof, -1, sizeof indexof);
	for(int i=0; i<ts.size(); i++) {
		indexof[ts[i]] = i;
	}
	if(indexof[1] == -1) return !(cout << 0);
	dp[0] = 1;
	for(int i=0; i<ts.size(); i++) {
		for(int a: adj[ts[i]]) {
			if(indexof[a] < i && reachable[a]) {
				return !(cout << "inf");
			}
			dp[indexof[a]] += dp[i];
			if(over[ts[i]]) over[a] = true;
			if(dp[indexof[a]] >= MOD) {
				dp[indexof[a]] -= MOD;
				over[a] = true;
			}
		}
	}
	printf(over[1] ? "%09d" : "%d", dp[indexof[1]]);
}
