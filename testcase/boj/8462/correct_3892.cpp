#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2, BUK = 317;
int a[MX], ans[MX], cnt[1000001];
struct query {
	int l, r, i;
};
query arr[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<m; i++) {
		cin >> arr[i].l >> arr[i].r;
		arr[i].l--;
		arr[i].r--;
		arr[i].i = i;
	}
	sort(arr, arr+m, [](query x, query y){
		return make_pair(x.l/BUK, x.r) < make_pair(y.l/BUK, y.r);
	});
	int l = 0, r = -1, cur = 0;
	for(int i=0; i<m; i++) {
		auto q = arr[i];
		while(r < q.r) {
			r++;
			cnt[a[r]]++;
			cur += (2*cnt[a[r]]-1)*a[r];
		}
		while(r > q.r) {
			cur -= (2*cnt[a[r]]-1)*a[r];
			cnt[a[r]]--;
			r--;
		}
		while(l < q.l) {
			cur -= (2*cnt[a[l]]-1)*a[l];
			cnt[a[l]]--;
			l++;
		}
		while(l > q.l) {
			l--;
			cnt[a[l]]++;
			cur += (2*cnt[a[l]]-1)*a[l];
		}
		ans[q.i] = cur;
	}
	for(int i=0; i<m; i++) {
		cout << ans[i] << '\n';
	}
}
