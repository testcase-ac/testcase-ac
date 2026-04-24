#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5002;
struct path {
	int u, w;
	bool operator<(const path& p) const {
		return w > p.w;
	}
};
vector<path> adjr[MX], adjl[MX];
int dist[MX], n, b, arr[MX], acc[MX], dp[MX][MX];
void dijk(vector<path> *adj) {
	memset(dist, 0x3f, sizeof dist);
	dist[b+1] = 0;
	priority_queue<path> pq;
	pq.push({b+1, 0});
	while(pq.size()) {
		auto [u, w] = pq.top();
		pq.pop();
		if(w > dist[u]) continue;
		for(auto [eu, ew]: adj[u]) {
			if(dist[eu] > w + ew) {
				dist[eu] = w + ew;
				pq.push({eu, dist[eu]});
			}
		}
	}
	for(int i=1; i<=b; i++)
		arr[i] += dist[i];
}
void f(int i, int l, int r, int optl, int optr) {
	if(l > r)
		return;
	int m = (l+r)/2, opt = optl;
	for(int j=optl; j<=min(m, optr); j++) {
		int val = dp[i-1][j-1]+(acc[m]-acc[j-1])*(m-j);
		if(val < dp[i][m]) {
			dp[i][m] = val;
			opt = j;
		}

	}
	f(i, l, m-1, optl, opt);
	f(i, m+1, r, opt, optr);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int s, r;
	cin >> n >> b >> s >> r;
	for(int i=0; i<r; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adjr[u].push_back({v, w});
		adjl[v].push_back({u, w});
	}
	dijk(adjr);
	dijk(adjl);
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	sort(arr+1, arr+b+1);
	for(int i=1; i<=b; i++) {
		acc[i] = acc[i-1] + arr[i];
	}
	for(int i=1; i<=s; i++) {
		f(i, 1, b, 1, b);
	}
	cout << dp[s][b];
}
