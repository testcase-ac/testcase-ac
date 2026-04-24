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
	set_t st;
	for(int i=1; i<=n; i++) {
		st.insert(i);
	}
	vector<int> ans(n+1);
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t;
		auto it = st.find_by_order(t);
		ans[*it] = i;
		st.erase(it);
	}
	for(int i=1; i<=n; i++)
		cout << ans[i] << '\n';
}
