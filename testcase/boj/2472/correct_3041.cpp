#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
vector<pair<int, int>> adj[MX];
int qry[MX], ans[MX];
map<int,int> dist2ind;
struct foo {
	int u, w;
	bool operator<(const foo& f) const {
		return w > f.w;
	}
};
void dijkstra(int src, vector<int>& dist) {
	priority_queue<foo> pq;
	pq.push({src, 0});
	dist[src] = 0;
	while(pq.size()) {
		int u = pq.top().u, w = pq.top().w;
		pq.pop();
		if(w != dist[u]) continue;
		for(auto e: adj[u]) {
			if(dist[e.first] > w+e.second ) {
				dist[e.first] = w+e.second;
				pq.push({e.first, dist[e.first]});
			}
		}
	}
}
struct segtree {
	vector<int> seg;
	int n;
	segtree(int _n) {
		n = _n;
		seg.resize(2*n, INT_MAX);
	}
	void upd(int i, int v) {
		i += n;
		seg[i] = min(seg[i], v);
		while(i /= 2)
			seg[i] = min(seg[i*2], seg[i*2+1]);
	}
	int qry(int l, int r) {
		l += n, r += n;
		int ret = INT_MAX;
		while(l < r) {
			if(l&1) ret = min(ret, seg[l++]);
			if(r&1) ret = min(ret, seg[--r]);
			l /= 2, r /= 2;
		}
		return ret;
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, a, b, c, m;
	cin >> n >> a >> b >> c >> m;
	vector<int> da(n+1, INT_MAX), db(n+1, INT_MAX), dc(n+1, INT_MAX);
	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	memset(qry, -1, sizeof qry);
	dijkstra(a, da);
	dijkstra(b, db);
	dijkstra(c, dc);
	vector<int> v(n);
	for(int i=0; i<n; i++)
		v[i] = i+1;
	sort(v.begin(), v.end(), [&](int i, int j){return da[i] < da[j];});
	for(int i=1; i<=n; i++) {
		dist2ind[db[i]] = 0;
	}
	int pt = 0;
	for(auto& pr: dist2ind)
		pr.second = pt++;
	segtree seg(pt);
	for(int i=0, j=0; i<n; i=j) {
		while(j < n && da[v[i]] == da[v[j]])
			j++;
		for(int k=i; k<j; k++) {
			int t = v[k];
			int qried = seg.qry(0, dist2ind[db[t]]);
			ans[t] = qried >= dc[t];
			//printf("for node %d: qried[0, %d]=%d, dc=%d\n", t, dist2ind[db[t]], qried, dc[t]);
		}
		for(int k=i; k<j; k++) {
			int t = v[k];

			seg.upd(dist2ind[db[t]], dc[t]);
			//printf("added to seg: node %d, index %d, val %d\n", t, dist2ind[db[t]], dc[t]);
		}
		//printf("two pointer for dist=%d ended\n", da[v[i]]);
	}
	int q;
	cin >> q;
	for(int i=0; i<q; i++) {
		int t;
		cin >> t;
		cout << (ans[t] ? "YES\n" : "NO\n");
	}
}
