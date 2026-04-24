#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	set_t ms;
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		ms.insert(t);
	}
	vector<int> a(n), ans(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=n-1; i>=0; i--) {
		auto it = ms.find_by_order(a[i]);
		ans[i] = *it;
		ms.erase(it);
	}
	for(int i=0; i<n; i++) {
		cout << ans[i] << '\n';
	}
}
