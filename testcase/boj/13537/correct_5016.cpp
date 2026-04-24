#include <bits/stdc++.h>
using namespace std;
vector<int> mst[200000];
int n;
int cnt(vector<int>& v, int k) {
	return v.end() - upper_bound(v.begin(), v.end(), k);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		mst[i+n] = {t};
	}
	for(int i=n-1; i; i--) {
		auto &v = mst[i], &vl = mst[2*i], &vr = mst[2*i+1];
		int a = 0, b = 0;
		while(a < vl.size() && b < vr.size()) {
			if(vl[a] < vr[b])
				v.push_back(vl[a++]);
			else
				v.push_back(vr[b++]);
		}
		while(a < vl.size())
			v.push_back(vl[a++]);
		while(b < vr.size())
			v.push_back(vr[b++]);
	}
	int q;
	cin >> q;
	while(q--) {
		int l, r, k, ans = 0;
		cin >> l >> r >> k;
		l += n-1, r += n;
		while(l < r) {
			if(l&1)
				ans += cnt(mst[l++], k);
			if(r&1)
				ans += cnt(mst[--r], k);
			l /= 2, r /= 2;
		}
		cout << ans << '\n';
	}
}
