#include <bits/stdc++.h>
using namespace std;
const int MX = 10001;
vector<int> adj[MX];
int w[MX], dp[2][MX];
bool seen[MX];
void dfs(int i) {
	seen[i] = 1;
	dp[1][i] = w[i];
	for(int a: adj[i]) {
		if(!seen[a]) {
			dfs(a);
			dp[0][i] += max(dp[0][a], dp[1][a]);
			dp[1][i] += dp[0][a];
		}
	}
}
vector<int> v;
void solve(int i, bool ok) {
	seen[i] = 1;
	bool use = ok && dp[1][i] > dp[0][i];
	if(use)
		v.push_back(i);
	for(int a: adj[i]) {
		if(!seen[a])
			solve(a, !use);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> w[i];
	}
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	cout << max(dp[0][1], dp[1][1]) << '\n';
	memset(seen, 0, sizeof seen);
	solve(1, 1);
	sort(v.begin(), v.end());
	for(int a: v)
		cout << a << ' ';
	sort(v.begin(), v.end());
}
