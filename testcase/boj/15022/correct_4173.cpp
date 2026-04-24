#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<tuple<int,int,int>,null_type,less<tuple<int,int,int>>,rb_tree_tag,tree_order_statistics_node_update> set_t;

set_t st;
const int MX = 1e5+2;
pair<int, int> scores[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		st.insert({0,0,i});
	}
	for(int i=0; i<m; i++) {
		int t, p;
		cin >> t >> p;
		st.erase({scores[t].first, scores[t].second, t});
		scores[t].first--;
		scores[t].second += p;
		st.insert({scores[t].first, scores[t].second, t});
		cout << st.order_of_key({scores[1].first, scores[1].second, 1}) + 1 << '\n';
	}
}
