#include <bits/stdc++.h>
using namespace std;
#define int long long
struct __attribute__((aligned(1), packed)) node {
	// l, r: 포인터
	int sum;
	int32_t l, r;
	char lazy_q;
	void set_lazy(int nl, int nr, int q) {
		if(q == 1) {
			sum = nr - nl + 1;
			lazy_q = 1;
		} else if(q == 2) {
			sum = 0;
			lazy_q = 2;
		} else if(q == 3){
			sum = (nr - nl + 1) - sum;
			if(lazy_q == 1) {
				lazy_q = 2;
			} else if(lazy_q == 2) {
				lazy_q = 1;
			} else if(lazy_q == 3) {
				lazy_q = 0;
			} else if(!lazy_q) {
				lazy_q = 3;
			}
		}
	}
};
node nodes[13000000]; // error 3
int nxt = 1;
const int MX = 1e18l+1;
// l, r: 쿼리 범위
// nl, nr nodes[ni]가 표현하는 범위
void update(int l, int r, int nl, int nr, int q, int ni) {
	node &n = nodes[ni];
	if(l > nr || r < nl) return;
	if(l <= nl && nr <= r) {
		n.set_lazy(nl, nr, q);
		return;
	}
	int m = (nl+nr)/2;
	if(!n.l) {
		n.l = nxt++;
		n.r = nxt++;
	}
	// before go down, apply lazy
	node &lft = nodes[n.l], &rht = nodes[n.r];
	lft.set_lazy(nl, m, n.lazy_q);
	rht.set_lazy(m+1, nr, n.lazy_q);
	n.lazy_q = 0;
	update(l, r, nl, m, q, n.l);
	update(l, r, m+1, nr, q, n.r);
	n.sum = lft.sum + rht.sum;
}

int query(int nl, int nr, int ni) {
	node &n = nodes[ni];
	int m = (nl+nr)/2;
	if(!n.l)
		return nl;
	// 여기서부터 n.l, n.r이 존재함은 보장됨.
	node &lft = nodes[n.l], &rht = nodes[n.r]; // error 1
	lft.set_lazy(nl, m, n.lazy_q);
	rht.set_lazy(m+1, nr, n.lazy_q);
	n.lazy_q = 0; // error 2
	if(!nodes[n.l].sum)
		return nl;
	else if(nodes[n.l].sum == (m-nl+1))
		return query(m+1, nr, n.r);
	else
		return query(nl, m, n.l);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int q, l, r;
		cin >> q >> l >> r;
		update(l, r, 1, MX, q, 0);
		cout << query(1, MX, 0) << '\n';
	}
}
