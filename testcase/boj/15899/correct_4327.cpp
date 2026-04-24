#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

inline int lsb(int i) {return i & -i;}
struct BIT {
	vector<ll> bit;
	BIT() {};
	BIT(int _n) { bit.resize(_n+1); };
	void update(int i, ll v) {
		while(i < sz(bit)) {
			bit[i] += v;
			i += lsb(i);
		}
	};
	ll query(int i) {
		ll ret = 0;
		while(i) {
			ret += bit[i];
			i -= lsb(i);
		}
		return ret;
	};
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m, c;
	cin >> n >> m >> c;
	vector<vector<int>> adj(n);
	vector<int> color(n), visittime(n), endtime(n), flattree(2*n+1);
	BIT treebit(2*n);
	vector<pair<int,int>> colorsorted(n);
	rep(i,n) {
		cin >> color[i];
		colorsorted[i].first = color[i];
		colorsorted[i].second = i;
	}
	sort(colorsorted.begin(), colorsorted.end());
	for(int i=0; i<n-1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<bool> seen(n);
	int t = 1;
	function<void(int)> dfs = [&](int i) {
		seen[i] = true;
		visittime[i] = t;
		flattree[t] = color[i];
		t++;
		for(int a: adj[i]) {
			if(!seen[a])
				dfs(a);
		}
		endtime[i] = t;
		flattree[t] = color[i];
		t++;
	};
	dfs(0);
	//printf("dfs ok\n");
	vector<pair<int,int>> querys(m);  // COLOR, NODE
	for(int i=0; i<m; i++) {
		cin >> querys[i].second >> querys[i].first;
		querys[i].second--;
	}
	sort(querys.begin(), querys.end());
	int cind = 0, qind = 0;
	ll ans = 0;
	for(int i=1; i<=c; i++) {
		//printf("start %dth number query\n", i);
		while(cind < n && colorsorted[cind].first == i) {
			int node = colorsorted[cind].second;
			treebit.update(visittime[node], 1);
			cind++;
			//printf("node %d updated at bit\n", node);
		}
		//printf("try entering query. qind=%d, m=%d, querys[qind].first=%d, i=%d\n", qind, m, querys[qind].first, i);
		while(qind < m && querys[qind].first == i) {
			int node = querys[qind].second;
			ll added = treebit.query(endtime[node]), subed = treebit.query(visittime[node]-1);
			ans += (added - subed);
			ans %= MOD;
			qind++;
			//printf("query at %d ok. added=%lld, subed=%lld\n", node, added, subed);
		}
	}
	cout << ans;
}
