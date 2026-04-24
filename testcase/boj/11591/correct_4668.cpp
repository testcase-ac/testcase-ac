#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long
typedef tree<int,null_type,greater_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
const int MX = 1000003;
int arr[MX], acc[MX], bit[MX];
int query(int t) {
	if(t <= 0)
		return 0;
	int res = 0;
	while(t) {
		res += bit[t];
		t -= t&-t;
	}
	return res;
}
void update(int t, int v) {
	while(t < MX) {
		bit[t] += v;
		t += t&-t;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, p;
	cin >> n;
	for(int i=1; i<=n; i++)
		cin >> arr[i];
	cin >> p;
	for(int i=1; i<=n; i++)
		arr[i] -= p;
	vector<int> keys = {0};
	for(int i=1; i<=n; i++) {
		acc[i] = acc[i-1] + arr[i];
		keys.push_back(acc[i]);
	}
	sort(keys.begin(), keys.end());
	keys.erase(unique(keys.begin(), keys.end()), keys.end());
	for(int i=0; i<=n; i++) {
		acc[i] = lower_bound(keys.begin(), keys.end(), acc[i])-keys.begin()+1;
		//printf("at i=%d, acc=%d\n", i, acc[i]);
		update(acc[i], 1);
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		update(acc[i], -1);
		ans += (n-i) - query(acc[i]-1);
	}
	cout << ans;
}
