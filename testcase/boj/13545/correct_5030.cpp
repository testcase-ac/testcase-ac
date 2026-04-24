#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2, BUK = 100, CNT = MX / BUK + 2;
int raw[MX], arr[MX], lst[MX], prep[CNT][CNT];
vector<int> posv[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, q;
	cin >> n;
	int mn = 0;
	for(int i=1; i<=n; i++) {
		cin >> raw[i];
		arr[i] = arr[i-1] + raw[i];
		mn = min(mn, arr[i]);
	}
	for(int i=0; i<=n; i++) {
		arr[i] -= mn;
		posv[arr[i]].push_back(i);
	}
	for(int i=0; i<n; i+=BUK) {
		memset(lst, -1, sizeof lst);
		int cur = 0;
		for(int j=i; j<n; j++) {
			if(lst[arr[j]] == -1) {
				lst[arr[j]] = j;
			} else {
				cur = max(cur, j - lst[arr[j]]);
			}
			if((j+1) % BUK == 0) {
				prep[i/BUK][j/BUK] = cur;
			}
		}
	}
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		l--;
		int lb = l / BUK, rb = r / BUK, cur = 0;
		if(lb + 1 <= rb - 1) {
			cur = prep[lb+1][rb-1];
		}
		for(int i=l; i <= r; i++) {
			auto &v = posv[arr[i]];
			auto it = upper_bound(v.begin(), v.end(), r);
			if(it != v.begin()) {
				cur = max(cur, *prev(it) - i);
			}
			if(i % BUK == BUK - 1)
				break;
		}
		for(int i=r; i >= l; i--) {
			auto &v = posv[arr[i]];
			auto it = lower_bound(v.begin(), v.end(), l);
			if(it != v.end()) {
				cur = max(cur, i - *it);
			}
			if(i % BUK == 0)
				break;
		}
		cout << cur << '\n';
	}
}
