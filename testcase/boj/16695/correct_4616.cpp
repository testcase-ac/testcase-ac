#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int MX = 1e5+2;
int par[MX], sz[MX], ans[MX], idx[MX];
tuple<int,int,int,int> buk[MX];
pii queries[MX];
vector<tuple<int,int,int,int>> lst;
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
void solve(int l, int r, int tlv) {
	if(l == r) {
		if(queries[l].first != -1 && f(queries[l].first) == f(queries[l].second) && ans[l] == -1) {
			ans[l] = tlv;
		}
		return;
	}
	int m = (l+r)/2;
	vector<pii> tmp;
	for(int i=m+1; i<=r; i++) {
		auto [t, u, v, lv] = buk[i];
		if(u != -1 && t < l && lv <= tlv) {
			tmp.push_back(join(u, v));
		}
	}
	if(r == M-1) {
		for(auto [t, u, v, lv]: lst) {
			if(t < l && lv <= tlv) {
				tmp.push_back(join(u, v));
			}
		}
	}
	solve(l, m, tlv);
	rollback(tmp);

	for(int i=l; i<=m; i++) {
		auto [t, u, v, lv] = buk[i];
		if(u != -1 && t > r && lv <= tlv) {
			tmp.push_back(join(u, v));
		}
	}
	solve(m+1, r, tlv);
	rollback(tmp);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(ans, -1, sizeof ans);
	memset(queries, -1, sizeof queries);
	memset(buk, -1, sizeof buk);
	cin >> n >> M;
	for(int i=0; i<n; i++) {
		par[i] = i;
		idx[i] = rand();
	}
	map<pii, pii> mp;
	for(int i=0; i<M; i++) {
		int t, u, v;
		cin >> t >> u >> v;
		if(u > v)
			swap(u, v);
		if(t == 0) {
			int lv;
			cin >> lv;
			mp[{u, v}] = {i, lv};
		} else if(t == 1) {
			auto pr = mp[{u,v}];
			buk[pr.first] = {i, u, v, pr.second};
			buk[i] = {pr.first, u, v, pr.second};
			mp.erase({u, v});
		} else {
			queries[i] = {u, v};
		}
	}
	for(auto [pr, pr2]: mp) {
		lst.push_back({pr2.first, pr.first, pr.second, pr2.second});
		buk[pr2.first] = {M, pr.first, pr.second, pr2.second};
	}
	for(int i=0; i<10; i++) {
		solve(0, M-1, i);
	}
	for(int i=0; i<M; i++) {
		if(queries[i].first != -1)
			cout << ans[i] << '\n';
	}
}
