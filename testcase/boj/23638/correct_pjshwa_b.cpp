#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()
typedef long long ll;
const int NMAX = 2e5 + 5;
vector<int> adj[NMAX], V, l;
int n, a, b, v[NMAX], chk[NMAX], ans, mxd, ix, sz;
multiset<int> s;

int dfs(int now, int bef) {
	if (v[now]) {
		ix = now;  return 1;
	}
	v[now] = 1;

	for (int nx : adj[now]) {
		if (nx == bef) continue;
		if (dfs(nx, now)) {
			V.emplace_back(now); chk[now] = 1;
			if (ix == now) return 0;
			return 1;
		}
	}
	return 0;
}

int dfs2(int now, int bef, int dist) {
	if (dist > mxd) {
		mxd = dist;
		ix = now;
	}

	for (int nx : adj[now]) {
		if (nx == bef || chk[nx]) continue;
		dfs2(nx, now, dist + 1);
	}
	return 0;
}

void init_tree(int root) {
	mxd = -1; chk[root] = 0;
	dfs2(root, -1, 0);
	l.emplace_back(mxd);

	mxd = -1;
	dfs2(ix, -1, 0);
	ans = max(ans, mxd);
	chk[root] = 1;
	return;
}

int main(void) {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	dfs(1, -1); sz = V.size();
	for (int r : V) init_tree(r);
	s.emplace(-1e9);
	for (int i = 0; i < sz; i++) {
		ans = max(ans, *s.rbegin() + i + l[i]);
		s.emplace(l[i] - i);
	}
	for (int i = 0; i < sz; i++) {
		s.erase(s.find(l[i] - i));
		ans = max(ans, *s.rbegin() + i + sz + l[i]);
	}
	cout << sz << ' ' << ans;
	return 0;
}
