#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
vector<pair<int, int>> adj[100001];
int closed[100001], open[100001];
void f(int i, int p) {
	bool isc = 1;
	for(auto [v, w]: adj[i]) {
		if(v == p) continue;
		f(v, i);
		closed[i] += open[v]+closed[v];
		isc = 0;
	}
	if(isc) {
		return;
	}
	vector<int> arr;
	int tsum = 0;
	for(auto [v, w]: adj[i]) {
		if(v == p) continue;
		arr.push_back(((open[v]+1)*w)%MOD);
		tsum += arr.back();
	}
	open[i] = (open[i] + tsum) % MOD;
	for(int t: arr) {
		tsum = (tsum-t+MOD)%MOD;
		closed[i] += t*tsum;
		closed[i] %= MOD;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		adj[a].push_back({b, w});
		adj[b].push_back({a, w});
	}
	f(1, 0);
	cout << (closed[1]+open[1])%MOD;
}
