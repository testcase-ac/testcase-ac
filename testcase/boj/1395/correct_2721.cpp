#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
int segt[2*MX], delay[MX], len[2*MX], n, h;
void apply(int p) {
	segt[p] = len[p] - segt[p];
	if(p < n) delay[p] ^= 1;
}
void push(int p) {
	for(int i=h; i; i--) {
		int t = p >> i;
		if(delay[t]) {
			delay[t] = 0;
			apply(t*2);
			apply(t*2+1);
		}
	}
}
void build(int p) {
	while(p /= 2) {
		segt[p] = segt[p*2] + segt[p*2+1];
		if(delay[p])
			segt[p] = len[p] - segt[p];
	}
}
void update(int l, int r) {
	l += n, r += n;
	int l0 = l, r0 = r;
	while(l < r) {
		if(l&1) apply(l++);
		if(r&1) apply(--r);
		l /= 2, r /= 2;
	}
	build(l0);
	build(r0-1);
}
int query(int l, int r) {
	l += n, r += n;
	push(l);
	push(r-1);
	int q = 0;
	while(l < r) {
		if(l&1) q += segt[l++];
		if(r&1) q += segt[--r];
		l /= 2, r /= 2;
	}
	return q;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m;
	cin >> n >> m;
	h = 32 - __builtin_clz(n);
	for(int i=n; i<2*n; i++)
		len[i] = 1;
	for(int i=n-1; i; i--)
		len[i] = len[2*i] + len[2*i+1];
	while(m--) {
		int o, s, t;
		cin >> o >> s >> t;
		if(!o)
			update(s-1, t);
		else
			cout << query(s-1, t) << '\n';
	}
}
