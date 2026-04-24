#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> Set;
vector<int> ans;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	Set s;
	int n, m, cur;
	cin >> n >> m;
	cur = m;
	for(int i=1; i<=n; i++) {
		s.insert(i);
	}
	for(int i=n; i>=1; i--) {
		ans.push_back(cur);
		int p = s.order_of_key(cur);
		s.erase(cur);
		if(i == 1) break;
		cur = *s.find_by_order((p+m-1)%(i-1));
	}
	cout << '<';
	for(int i=0; i<n; i++) {
		cout << ans[i];
		if(i != n-1) cout << ", ";
	}
	cout << '>';
}
