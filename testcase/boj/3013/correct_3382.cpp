#include <bits/stdc++.h>
using namespace std;

int n, b;
vector<int> lv, rv;
map<int, int> lcnt, rcnt;
void build(map<int, int> &mp, vector<int> &v) {
	int acc = 0;
	for(int i: v) {
		mp[acc]++;
		acc += (i > b ? 1 : -1);
	}
	mp[acc]++;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> b;
	int t;
	while(cin >> t, t != b)
		lv.push_back(t);
	while(cin >> t)
		rv.push_back(t);
	reverse(lv.begin(), lv.end());
	build(lcnt, lv);
	build(rcnt, rv);
	int ans = 0;
	for(const auto &pr: lcnt) {
		ans += pr.second * rcnt[-pr.first];
	}
	cout << ans;
}
