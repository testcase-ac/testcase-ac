#include <bits/stdc++.h>
using namespace std;
#define int long long
int cnt[1001], cntp[1001];
pair<int, int> solve() {
	int n, c, m;
	cin >> n >> c >> m;
	memset(cnt, 0, sizeof cnt);
	memset(cntp, 0, sizeof cntp);
	multiset<int> st;
	for(int i=0; i<m; i++) {
		int p, b;
		cin >> p >> b;
		cntp[p]++;
		cnt[b]++;
		st.insert(p);
	}
	int trip = 0;
	while(st.size()) {
		trip++;
		for(int i=1; i<1001; i++) {
			auto it = st.lower_bound(i);
			if(it == st.end())
				break;
			st.erase(it);
		}
	}
	trip = max(trip, *max_element(cnt, cnt+1001));
	int ans = 0;
	for(int i=1; i<1001; i++) {
		ans += max(cntp[i]-trip, 0ll);
	}
	return {trip, ans};
}
int32_t main() {
	int t;
	cin >> t;
	for(int i=1; i<=t; i++) {
		auto s = solve();
		printf("Case #%d: %d %d\n", i, s.first, s.second);
	}
}
