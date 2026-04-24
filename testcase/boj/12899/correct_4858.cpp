#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	set_t st;
	while(n--) {
		int s, x;
		cin >> s >> x;
		if(s == 1) {
			st.insert(x);
		} else {
			auto it = st.find_by_order(x-1);
			cout << *it << '\n';
			st.erase(it);
		}
	}
}
