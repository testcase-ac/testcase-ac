#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2, MXA = 1e6+2, TH = sqrt(MX);
struct query {
	int l, r, i;
};
int arr[MX], cnt[MXA], ans[MX], cur = 1;
query qry[MX];
int sign(int i) {
	return i > 0 ? 1 : -1;
}
void add(int i) {
	if(!cnt[arr[i]])
		cur++;
	cnt[arr[i]]++;
}
void rm(int i) {
	cnt[arr[i]]--;
	if(!cnt[arr[i]])
		cur--;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	cin >> m;
	for(int i=0; i<m; i++) {
		cin >> qry[i].l >> qry[i].r;
		qry[i].i = i;
	}
	sort(qry, qry+m, [](query& a, query& b) {
		return make_pair(a.l/TH, a.r) < make_pair(b.l/TH, b.r);
	});
	int l = 1, r = 1;
	cnt[arr[1]] = 1;
	for(int i=0; i<m; i++) {
		query& q = qry[i];
		while(l < q.l)
			rm(l++);
		while(l > q.l)
			add(--l);
		while(r < q.r)
			add(++r);
		while(r > q.r)
			rm(r--);
		ans[q.i] = cur;
	}
	for(int i=0; i<m; i++) {
		cout << ans[i] << '\n';
	}
}
