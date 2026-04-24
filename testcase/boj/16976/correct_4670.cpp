#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
vector<int> buk[MX];
struct game {
	int l, r;
	vector<int> ppl;
};
game games[MX];
pair<int, int> edges[MX];
int par[MX];
int f(int i) {
	return par[i] == i ? i : par[i] = f(par[i]);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t;
		games[t].ppl.push_back(i);
	}
	for(int i=1; i<=m; i++) {
		games[i].l = 0;
		games[i].r = q+1;
		buk[(q+1)/2].push_back(i);
	}
	for(int i=1; i<=q; i++) {
		cin >> edges[i].first >> edges[i].second;
	}
	bool ok = 0;
	while(!ok) {
		ok = 1;
		for(int i=1; i<=n; i++) {
			par[i] = i;
		}
		for(int i=0; i<=q; i++) {
			if(i) {
				auto [u, v] = edges[i];
				if(f(u) != f(v))
					par[f(u)] = f(v);
			}
			for(int idx: buk[i]) {
				game &g = games[idx];
				bool gok = 1;
				for(int p: g.ppl) {
					if(f(p) != f(g.ppl.front())) {
						gok = 0;
						break;
					}
				}
				if(gok) {
					g.r = i;
				} else {
					g.l = i+1;
				}
			}
		}
		for(int i=0; i<=q; i++) {
			buk[i].clear();
		}
		for(int i=1; i<=m; i++) {
			game &g = games[i];
			if(g.l != g.r) {
				ok = 0;
				buk[(g.l+g.r)/2].push_back(i);
			}
		}
	}
	for(int i=1; i<=m; i++) {
		if(games[i].l == q+1)
			cout << "-1\n";
		else
			cout << games[i].l << '\n';
	}
}
