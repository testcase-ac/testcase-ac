#include <bits/stdc++.h>
using namespace std;
map<int, int> st, ed;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int l, r;
		cin >> l >> r;
		st[l]++;
		ed[r]++;
	}
	auto i = st.begin(), j = ed.begin();
	int cnt = 0, ans = 0;
	while(i != st.end()) {
		cnt += i->second;
		while(j->first <= i->first) {
			cnt -= j->second;
			j++;
		}
		i++;
		ans = max(ans, cnt);
	}
	cout << ans;
}
