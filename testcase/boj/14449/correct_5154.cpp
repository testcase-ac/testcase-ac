#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	set_t str, stl;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
		str.insert(v[i]);
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		str.erase(v[i]);
		int rc = str.size() - str.order_of_key(v[i]), lc = stl.size() - stl.order_of_key(v[i]);
		if(min(rc,lc)*2 < max(rc, lc))
			ans++;
		stl.insert(v[i]);
	}
	cout << ans;
}
