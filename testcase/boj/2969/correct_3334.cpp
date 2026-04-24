#include <bits/stdc++.h>
using namespace std;
struct segtree {
	vector<int> tree;
	int n;
	segtree(int _n) {n = _n; tree.resize(2*n);}
	int query(int l, int r) {
		l += n, r += n;
		int mx = 0;
		while(l < r) {
			if(l&1) mx = max(mx, tree[l++]);
			if(r&1) mx = max(mx, tree[--r]);
			l /= 2, r /= 2;
		}
		return mx;
	}
	void update(int i, int v) {
		i += n;
		tree[i] = v;
		while(i /= 2) {
			tree[i] = max(tree[i*2], tree[i*2+1]);
		}
	}
};
int arr[1500][1500], dp[1500][1500];
int at(pair<int, int> p) {
	return arr[p.first][p.second];
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ar, ac;
	cin >> n >> ar >> ac;
	ar--;
	ac--;
	vector<pair<int, int>> pos(n*n);
	vector<segtree> horseg(n, n), verseg(n, n);
	int nxt = 0;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
			pos[nxt++] = {i, j};
		}
	}
	sort(pos.begin(), pos.end(), [](pair<int, int> a, pair<int, int> b) {
		return at(a) > at(b);
	});
	for(int i=0, j=0; i<n*n; i=j) {
		while(j < n*n && at(pos[i]) == at(pos[j]))
			j++;
		for(int t=i; t<j; t++) {
			auto [r, c] = pos[t];
			int mx = 0;
			if(r)
				mx = max({mx, horseg[r-1].query(0, c-1), horseg[r-1].query(c+2, n)});
			if(r+1 < n)
				mx = max({mx, horseg[r+1].query(0, c-1), horseg[r+1].query(c+2, n)});
			if(c)
				mx = max({mx, verseg[c-1].query(0, r-1), verseg[c-1].query(r+2, n)});
			if(c+1 < n)
				mx = max({mx, verseg[c+1].query(0, r-1), verseg[c+1].query(r+2, n)});
			mx++;
			dp[r][c] = mx;
			if(tie(r, c) == tie(ar, ac))
				return !(cout << mx);
		}
		for(int t=i; t<j; t++) {
			auto [r, c] = pos[t];
			horseg[r].update(c, dp[r][c]);
			verseg[c].update(r, dp[r][c]);
		}
	}
}
