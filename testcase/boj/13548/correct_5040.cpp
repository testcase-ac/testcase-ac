#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2, SQ = 317;
struct info {
	int l, r, i;
};
int a[MX], cnt[MX], cnt2[MX], ans[MX], cans;
info qry[MX];
void add(int t) {
	cnt2[cnt[t]]--;
	cnt[t]++;
	cnt2[cnt[t]]++;
	if(cnt[t] > cans)
		cans = cnt[t];
}
void remove(int t) {
	cnt2[cnt[t]]--;
	cnt[t]--;
	cnt2[cnt[t]]++;
	if(!cnt2[cans])
		cans--;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	cnt2[0] = n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}
	int q;
	cin >> q;
	for(int i=0; i<q; i++) {
		int l, r;
		cin >> l >> r;
		qry[i] = {l, r, i};
	}
	sort(qry, qry+q, [](info x, info y){
		return (x.l / SQ == y.l / SQ) ? x.r < y.r : x.l < y.l;
	});
	int l = 1, r = 0;
	for(int i=0; i<q; i++) {
		while(r < qry[i].r) {
			r++;
			add(a[r]);
		}
		while(r > qry[i].r) {
			remove(a[r]);
			r--;
		}
		while(l < qry[i].l) {
			remove(a[l]);
			l++;
		}
		while(l > qry[i].l) {
			l--;
			add(a[l]);
		}
		ans[qry[i].i] = cans;
	}
	for(int i=0; i<q; i++) {
		cout << ans[i] << '\n';
	}
}
