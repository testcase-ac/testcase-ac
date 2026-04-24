#include <bits/stdc++.h>
using namespace std;
#define int long long
int lst[1000001], n;
pair<int, int> seg[2000000];
void build() {
	for(int i=n-1; i; i--) {
		seg[i] = max(seg[i*2+1], seg[i*2]);
	}
}
pair<int, int> query(int l, int r) {
	l += n, r += n;
	pair<int, int> ret = {INT_MIN, INT_MIN};
	while(l < r) {
		if(l&1) ret = max(ret, seg[l++]);
		if(r&1) ret = max(ret, seg[--r]);
		l /= 2, r /= 2;
	}
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int x;
	cin >> n >> x;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	fill(lst, lst+1000001, INT_MIN);
	fill(seg, seg+2000000, make_pair(INT_MIN, INT_MIN));
	multiset<int> ms;
	for(int i=0; i<n; i++) {
		ms.insert(v[i]);
		if(i >= x) {
			ms.erase(ms.find(v[i-x]));
		}
		if(i >= x-1) {
			seg[n+i+1-x].first = *ms.begin();
			seg[n+i+1-x].second = i+1-x;
		}
	}
	build();
	int anscnt = 0, ans = 0;
	for(int i=0; i<n; i++) {
		auto [h, j] = query(max(0ll,i+1-x), i+1);
		ans += v[i] - h;
		if(i >= lst[h]+x) {
			lst[h] = j;
			anscnt++;
		}
	}
	cout << ans << '\n' << anscnt;
}
