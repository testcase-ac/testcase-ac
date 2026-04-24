#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 1e5+2, MXL = 2e6;
struct node {
	ll v;
	node *l, *r;
};
int nxt = 1;
node *roots[MX];
node orig[MXL];
int _n = 0;
node* alloc(){return &orig[_n++];}
ll arr[MX], acc[MX];
node* build(int l, int r) {
	node* n = alloc();
	if(l == r) {
		n->v = arr[l];
	} else {
		int m = (l+r)/2;
		n->v = acc[r] - acc[l-1];
		n->l = build(l, m);
		n->r = build(m+1, r);
	}
	return n;
}
node* update(node* ref, int l, int r, int i, ll d) {
	node* n = alloc();
	n->v = ref->v+d;
	if(l != r) {
		int m = (l+r)/2;
		if(i <= m) {
			n->l = update(ref->l, l, m, i, d);
			n->r = ref->r;
		} else {
			n->l = ref->l;
			n->r = update(ref->r, m+1, r, i, d);
		}
	}
	return n;
}
ll query(node* n, int l, int r, int ls, int rs) {
	if(l == ls && r == rs)
		return n->v;
	int m = (l+r)/2;
	if(rs <= m)
		return query(n->l, l, m, ls, rs);
	else if(ls > m)
		return query(n->r, m+1, r, ls, rs);
	else
		return query(n->l, l, m, ls, m)+query(n->r, m+1, r, m+1, rs);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		acc[i] = acc[i-1] + arr[i];
	}
	roots[0] = build(1, n);
	int m;
	cin >> m;
	while(m--) {
		int t;
		cin >> t;
		if(t == 1) {
			int i;
			ll v;
			cin >> i >> v;
			roots[nxt] = update(roots[nxt-1], 1, n, i, v-arr[i]);
			nxt++;
			arr[i] = v;
		} else {
			int k, i, j;
			cin >> k >> i >> j;
			cout << query(roots[k], 1, n, i, j) << '\n';
		}
	}
}
