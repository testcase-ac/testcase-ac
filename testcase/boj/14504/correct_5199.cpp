#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
const int MX = 131072;
int k;
set_t seg[MX*2];
int cnt(set_t &s) {
	return s.size() - s.order_of_key(k+1);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, off;
	cin >> n;
	off = n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		seg[off+i].insert(t);
	}
	for(int i=off-1; i; i--) {
		seg[i] = seg[2*i];
		for(int t: seg[2*i+1])
			seg[i].insert(t);
	}
	int m;
	cin >> m;
	while(m--) {
		int t;
		cin >> t;
		if(t == 1) {
			int l, r;
			cin >> l >> r >> k;
			l--;
			l += off, r += off;
			int ans = 0;
			while(l < r) {
				if(l&1)
					ans += cnt(seg[l++]);
				if(r&1)
					ans += cnt(seg[--r]);
				l /= 2, r /= 2;
			}
			cout << ans << '\n';
		} else {
			int i;
			cin >> i >> k;
			i += off-1;
			int e = *seg[i].begin();
			while(i) {
				seg[i].erase(prev(seg[i].lower_bound(e)));
				seg[i].insert(k);
				i /= 2;
			}
		}

	}
}
