#include <bits/stdc++.h>
using namespace std;
const int MX = 1024;
int n;
struct ST {
	int segt[MX*2];
	void update(int i, int v) {
		i += n;
		segt[i] = v;
		while(i /= 2)
			segt[i] = segt[i*2]+segt[i*2+1];
	}
	int query(int l, int r) { // [l, r]
		l += n, r += n+1;
		int v = 0;
		while(l < r) {
			if(l&1) v += segt[l++];
			if(r&1) v += segt[--r];
			l /= 2, r /= 2;
		}
		return v;
	}
};
ST segt[2*MX];
void update(int x, int y, int c) {
	x += n;
	segt[x].update(y, c);
	while(x /= 2)
		segt[x].update(y, segt[x*2].segt[n+y]+segt[x*2+1].segt[n+y]);
}
int query(int x1, int x2, int y1, int y2) {
	int r = 0;
	x1 += n, x2 += n+1;
	while(x1 < x2) {
		if(x1&1) r += segt[x1++].query(y1, y2);
		if(x2&1) r += segt[--x2].query(y1, y2);
		x1 /= 2, x2 /= 2;
	}
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			int t;
			cin >> t;
			update(i, j, t);
		}
	}
	while(m--) {
		int t;
		cin >> t;
		if(t) {
			int x1, x2, y1, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			cout << query(x1-1, x2-1, y1-1, y2-1) << '\n';
		} else {
			int x, y, c;
			cin >> x >> y >> c;
			update(x-1, y-1, c);
		}
	}
}
