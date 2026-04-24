#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+3;
int seg[MX*2];
void upd(int i, int v) {
	i += MX;
	seg[i] = v;
	while(i /= 2)
		seg[i] = min(seg[i*2], seg[i*2+1]);
}
int qry(int l, int r) {
	l += MX-1, r += MX;
	int ret = 1e9;
	while(l < r) {
		if(l&1) ret = min(ret, seg[l++]);
		if(r&1) ret = min(ret, seg[--r]);
		l /= 2, r /= 2;
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		upd(i, t);
	}
	int m;
	cin >> m;
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a == 1)
			upd(b-1, c);
		else
			cout << qry(b, c) << '\n';
	}
}
