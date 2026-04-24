#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct comp {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
		return a.second == b.second ? a.first < b.first : a.second < b.second;
	}
};
typedef tree<pair<int, int>,null_type,comp,rb_tree_tag,tree_order_statistics_node_update> set_t;
pair<int, int> arr[75000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		set_t st;
		long long ans = 0;
		for(int i=0; i<n; i++) {
			cin >> arr[i].first >> arr[i].second;
			st.insert(arr[i]);
		}
		sort(arr, arr+n);
		int j = 0;
		for(int i=0; i<n;) {
			while(j < n && arr[i].first == arr[j].first) {
				ans += st.order_of_key({arr[j].first, arr[j].second+1})-1;
				j++;
			}
			while(i < j) {
				st.erase(arr[i++]);
			}
		}
		cout << ans << '\n';
	}
}
