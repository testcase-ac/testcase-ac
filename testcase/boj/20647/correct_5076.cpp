#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+7;
vector<int> adj[MX];

int dfs(int i, int p) {
	int child = 0, sum = 0;
	for(int a: adj[i]) {
		if(a == p) continue;
		child++;
		sum += dfs(a, i);
	}
	if(!child)
		return 0;
	else
		return 64 - __builtin_clzll(child) + child + sum;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << dfs(1, 0);
}
