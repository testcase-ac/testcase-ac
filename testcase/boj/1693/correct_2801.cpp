#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
vector<int> adj[MX];
int dp[MX][20], cost[20], mnp[21], mns[21];
bool seen[MX];
void dfs(int i) {
	for(int j=1; j<20; j++)
		dp[i][j] = j;
	seen[i] = 1;
	for(int a: adj[i]) {
		if(!seen[a]) {
			dfs(a);
			mnp[0] = 1e9;
			for(int j=1; j<20; j++)
				mnp[j] = min(mnp[j-1], dp[a][j]);
			mns[20] = 1e9;
			for(int j=19; j>=1; j--)
				mns[j] = min(mns[j+1], dp[a][j]);
			for(int j=1; j<20; j++)
				dp[i][j] += min(mnp[j-1], mns[j+1]);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	cout << *min_element(dp[1]+1, dp[1]+20);
}
