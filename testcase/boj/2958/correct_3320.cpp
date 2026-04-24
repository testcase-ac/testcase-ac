#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1502, MOD = 1e9+7;
struct edge {
	int v, d, i;
};
struct custom {
	int u, w;
	bool operator<(const custom& c) const {
		return w > c.w;
	}
};
int modinv(int a, int b=MOD-2) {
    int ret = 1, mult = a % MOD;
    while(b) {
        if(b&1) ret = (ret*mult)%MOD;
        mult = (mult*mult)%MOD;
        b /= 2;
    }
    return ret;
}
vector<edge> adj[MX];
vector<pair<int, int>> subg[MX], subginv[MX]; // node, edge
int ans[5001], tans[5001], dist[MX], cnt[MX], reach[MX], n, m;
bool spreaded[5001];
void dijk(int st) {
	memset(dist, 0x3f, sizeof dist);
	memset(cnt, 0, sizeof cnt);
	memset(tans, 0, sizeof tans);
	memset(spreaded, 0, sizeof spreaded);
	for(int i=1; i<=n; i++) {
		subg[i].clear();
		subginv[i].clear();
	}
	dist[st] = 0;
	cnt[st] = 1;
	priority_queue<custom> pq;
	pq.push({st, 0});
	vector<int> stk;
	while(pq.size()) {
		auto p = pq.top();
		pq.pop();
		int u = p.u, w = p.w;
		if(w > dist[u]) continue;
		stk.push_back(u);
		for(auto e: adj[u]) {
			if(w+e.d < dist[e.v]) {
				dist[e.v] = w+e.d;
				pq.push({e.v, dist[e.v]});
				cnt[e.v] = cnt[u];
				subginv[e.v] = {{u, e.i}}; // error 1
			} else if(w+e.d == dist[e.v]) {
				cnt[e.v] += cnt[u];
				cnt[e.v] %= MOD;
				subginv[e.v].push_back({u, e.i});
			}
		}
	}
	for(int i=1; i<=n; i++) { // error 2
		for(auto [ev, ei]: subginv[i]) {
			subg[ev].push_back({i, ei});
		}
	}
	memset(reach, 0, sizeof reach);
	while(stk.size()) {
		int i = stk.back();
		stk.pop_back();
		reach[i] = 1;
		for(auto [ev, ei]: subg[i]) {
			reach[i] += reach[ev];
			reach[i] %= MOD;
		}
		for(auto [ev, ei]: subginv[i]) {
			tans[ei] = reach[i]*cnt[ev];
			tans[ei] %= MOD;
		}
	}
	//printf("at st=%d\n", st);
	for(int i=0; i<m; i++) {
		//printf("  i=%d: tans=%d\n", i, tans[i]);
		ans[i] += tans[i];
		ans[i] %= MOD;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		adj[u].push_back({v, d, i});
	}
	for(int i=1; i<=n; i++) {
		dijk(i);
	}
	for(int i=0; i<m; i++)
		cout << ans[i] % MOD << '\n';
}
