#include <bits/stdc++.h>
using namespace std;
int cnt[10001], arr[300001], ans[10000], total;
const int BUK = 3000; // (N^2/B+QB)' = 0
struct query {
	int l, r, i;
};
query qry[10000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, c;
	cin >> n >> c;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	int q;
	cin >> q;
	for(int i=0; i<q; i++) {
		cin >> qry[i].l >> qry[i].r;
		qry[i].r++;
		qry[i].i = i;
	}
	sort(qry, qry+q, [](query a, query b) {
		return a.l/BUK == b.l/BUK ? a.r < b.r : a.l < b.l;
	});
	int l = qry[0].l, r = l;
	for(int i=0; i<q; i++) {
		while(r < qry[i].r) {
			cnt[arr[r]]++;
			r++;
		}
		while(r > qry[i].r) {
			r--;
			cnt[arr[r]]--;
		}
		while(l < qry[i].l) {
			cnt[arr[l]]--;
			l++;
		}
		while(l > qry[i].l) {
			l--;
			cnt[arr[l]]++;
		}
		for(int j=1; j<=c; j++) {
			if(cnt[j] > (r-l)/2) {
				ans[qry[i].i] = j;
				break;
			}
		}
	}
	for(int i=0; i<q; i++) {
		if(ans[i]) {
			cout << "yes " << ans[i] << '\n';
		} else {
			cout << "no\n";
		}
	}
}
