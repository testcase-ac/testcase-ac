#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int MX = 1e5+2;
int par[MX], sz[MX], ans[MX], idx[MX];
tuple<int,int,int> buk[MX];
pii queries[MX];
vector<tuple<int,int,int>> lst;
int f(int i) {return i == par[i] ? i : f(par[i]);}
pii join(int a, int b) { // returns changed index, original pointer
	a = f(a), b = f(b);
	if(idx[a] < idx[b])
		swap(a, b);
	int orig = par[b];
	par[b] = a;
	return {b, orig};
}
void rollback(vector<pii>& tmp) {
	while(tmp.size()) {
		auto [i, p] = tmp.back();
		par[i] = p;
		tmp.pop_back();
	}
}
int n, M;
void solve(int l, int r) {
	if(l == r) {
		if(queries[l].first) {
			ans[l] = (f(queries[l].first) == f(queries[l].second));
		}
		return;
	}
	int m = (l+r)/2;
	vector<pii> tmp;
	for(int i=m+1; i<=r; i++) {
		auto [t, u, v] = buk[i];
		if(u && t < l) {
			tmp.push_back(join(u, v));
		}
	}
	if(r == M-1) {
		for(auto [t, u, v]: lst) {
			if(t < l) {
				tmp.push_back(join(u, v));
			}
		}
	}
	solve(l, m);
	rollback(tmp);

	for(int i=l; i<=m; i++) {
		auto [t, u, v] = buk[i];
		if(u && t > r) {
			tmp.push_back(join(u, v));
		}
	}
	solve(m+1, r);
	rollback(tmp);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(ans, -1, sizeof ans);
	cin >> n >> M;
	for(int i=1; i<=n; i++) {
		par[i] = i;
		idx[i] = rand();
	}
	map<pii, int> mp;
	for(int i=0; i<M; i++) {
		int t, u, v;
		cin >> t >> u >> v;
		if(u > v)
			swap(u, v);
		if(t == 1) {
			mp[{u, v}] = i;
		} else if(t == 2) {
			buk[mp[{u, v}]] = {i, u, v};
			buk[i] = {mp[{u,v}], u, v};
			mp.erase({u, v});
		} else {
			queries[i] = {u, v};
		}
	}
	for(auto [pr, t]: mp) {
		lst.push_back({t, pr.first, pr.second});
		buk[t] = {M, pr.first, pr.second};
	}
	solve(0, M-1);
	for(int i=0; i<M; i++) {
		if(ans[i] != -1)
			cout << ans[i] << '\n';
	}
}
