#include <bits/stdc++.h>
using namespace std;
const int MX = 3e5+2;
struct Node {
	int l, r, d;
};
int segt[MX*2], delay[MX], n;
Node arr[MX];
void apply(int p, int val) {
	segt[p] = val;
	if(p < n)
		delay[p] = val;
}
void pull(int p) {
	for(int i=19; i>0; i--) {
		int t = p >> i;
		if(delay[t] != -1) {
			apply(t*2, delay[t]);
			apply(t*2+1, delay[t]);
			delay[t] = -1;
		}
	}
}
void update(int l, int r, int v) {  // [l, r]
	l += n, r += n+1;
	pull(l);
	pull(r-1);
	while(l < r) {
		if(l&1) apply(l++, v);
		if(r&1) apply(--r, v);
		l /= 2, r /= 2;
	}
}
int query(int p) {
	p += n;
	pull(p);
	return segt[p];
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(delay, -1, sizeof delay);
	cin >> n;
	int t;
	long long ans = 0;
	cin >> t;
	t--;
	arr[t].l = 0, arr[t].r = n-1;
	update(0, n-1, t);
	cout << "0\n";
	for(int i=0; i<n-1; i++) {
		cin >> t;
		t--;
		int p = query(t);
		if(t > p) {
			arr[t].l = p+1;
			arr[t].r = arr[p].r;
		} else {
			arr[t].l = arr[p].l;
			arr[t].r = p-1;
		}
		update(arr[t].l, arr[t].r, t);
		arr[t].d = arr[p].d+1;
		ans += arr[t].d;
		cout << ans << '\n';
	}
}
