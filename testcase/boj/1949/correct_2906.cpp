#include <bits/stdc++.h>
using namespace std;
const int MX = 1e4+2;
vector<int> adj[MX];
int val[MX], dp[MX][3];
bool seen[MX];
void dfs(int i) {
	seen[i] = 1;
	int par = -1, tot = 0;
	for(int a: adj[i]) {
		if(!seen[a]) {
			dfs(a);
			tot += max({dp[a][0], dp[a][1], dp[a][2]});
		}
		else
			par = a;
	}
	dp[i][0] = val[i];
	dp[i][1] = INT_MIN;
	for(int a: adj[i]) {
		if(a == par) continue;
		dp[i][0] += max(dp[a][1], dp[a][2]);
		dp[i][1] = max(dp[i][1], tot-max({dp[a][0],dp[a][1],dp[a][2]})+dp[a][0]);
		dp[i][2] += dp[a][1];
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> val[i];
	}
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	cout << max({dp[1][0],dp[1][1],dp[1][2]});
}
