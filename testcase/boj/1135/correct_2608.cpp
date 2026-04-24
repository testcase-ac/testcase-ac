#include <bits/stdc++.h>
using namespace std;
int dp[51];
vector<int> adj[51];
void dfs(int i, int p) {
	bool child = 1;
	vector<int> v;
	for(int a: adj[i]) {
		if(a == p) continue;
		child = 0;
		dfs(a, i);
		v.push_back(dp[a]);
	}
	if(child) return;
	sort(v.begin(), v.end(), greater<int>());
	for(int k=0; k<v.size(); k++) {
		dp[i] = max(dp[i], k+1+v[k]);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		if(!i) continue;
		adj[i].push_back(t);
		adj[t].push_back(i);
	}
	dfs(0, -1);
	cout << dp[0];
}
