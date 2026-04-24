#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
vector<int> v;
pair<int, int> seg[MX*2];
pair<int, int> merge(pair<int, int>& a, pair<int, int> &b) {
	v.clear();
	v.push_back(a.first);
	v.push_back(a.second);
	v.push_back(b.first);
	v.push_back(b.second);
	sort(v.begin(), v.end(), greater<int>());
	return {v[0], v[1]};
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(seg, -1, sizeof seg);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> seg[i+n].first;
	}
	for(int i=n-1; i; i--)
		seg[i] = merge(seg[i*2], seg[i*2+1]);
	int q;
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int i, x;
			cin >> i >> x;
			i--;
			i += n;
			seg[i].first = x;
			while(i /= 2)
				seg[i] = merge(seg[i*2], seg[i*2+1]);
		} else {
			pair<int, int> res = {-1, -1};
			int l, r;
			cin >> l >> r;
			l--;
			l += n;
			r += n;
			while(l < r) {
				if(l&1) res = merge(res, seg[l++]);
				if(r&1) res = merge(res, seg[--r]);
				l /= 2, r /= 2;
			}
			cout << res.first + res.second << '\n';
		}
	}
}
