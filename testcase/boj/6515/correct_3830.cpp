#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int MX = 1e5+2;
int seg[MX*2], a[MX], n;
vector<int> v;
int query(int l, int r) {
	l += n, r += n;
	int res = 0;
	while(l < r) {
		if(l&1) res = max(res, seg[l++]);
		if(r&1) res = max(res, seg[--r]);
		l /= 2, r /= 2;
	}
	return res;
}
// 3 5 8
void solve() {
	ios::sync_with_stdio(0);cin.tie(0);
	int q;
	cin >> n;
	if(!n)
		exit(0);
	cin >> q;
	memset(seg, 0, sizeof seg);
	v.clear();
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0, j=0; i<n; i=j) {
		while(j < n && a[i] == a[j])
			j++;
		seg[n+i] = (j-i);
		v.push_back(i);
	}
	for(int i=n-1; i; i--) {
		seg[i] = max(seg[i*2], seg[i*2+1]);
	}
	while(q--) {
		int l, r;
		cin >> l >> r;
		l--;
		auto it1 = lower_bound(v.begin(), v.end(), l), it2 = lower_bound(v.begin(), v.end(), r)-1;
		if(it1 > it2) {
			cout << (r-l) << '\n';
		} else if(it1 == it2) {
			cout << max(*it1 - l, r-*it2) << '\n';
		} else {
			int ans = max(max(*it1 - l, r-*it2), query(*it1, *it2));
			cout << ans << '\n';
		}
	}
}
int main() {
	while(1)
		solve();
}
