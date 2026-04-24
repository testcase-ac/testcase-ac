#include <bits/stdc++.h>
using namespace std;
#define int long long
struct range {
	int mx, lmx, rmx, sum, l, r;
};
range comb(range l, range r) {
	range ret;
	ret.mx = max({l.mx, r.mx, l.rmx+r.lmx});
	ret.l = l.l;
	ret.r = r.r;
	ret.lmx = max(l.lmx, l.sum + r.lmx);
	ret.rmx = max(r.rmx, r.sum + l.rmx);
	ret.sum = l.sum + r.sum;
	return ret;
}
const int N = 131072, INF = LLONG_MIN/3;
range arr[262144];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		arr[i+N] = {t, t, t, t, i, i};
	}
	for(int i=N-1; i; i--) {
		arr[i] = comb(arr[2*i], arr[2*i+1]);
	}
	int q;
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		l--;
		l += N, r += N;
		vector<range> lft, rht;
		while(l < r) {
			if(l&1) lft.push_back(arr[l++]);
			if(r&1) rht.push_back(arr[--r]);
			l /= 2;
			r /= 2;
		}
		reverse(rht.begin(), rht.end());
		lft.insert(lft.end(), rht.begin(), rht.end());
		for(int i=1; i<lft.size(); i++) {
			lft[0] = comb(lft[0], lft[i]);
		}
		cout << lft[0].mx << '\n';
	}
}  
