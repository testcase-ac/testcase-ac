#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
int arr[250000];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k, ans = 0;
	cin >> n >> k;
	set_t ms;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		ms.insert(arr[i]);
		if(i >= k) {
			auto it = ms.upper_bound(arr[i-k]);
			ms.erase(it);
		}
		if(i >= k-1)
			ans += *ms.find_by_order((k-1)/2);
	}
	cout << ans;
}
