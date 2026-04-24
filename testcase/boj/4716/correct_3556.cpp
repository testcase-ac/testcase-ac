#include <bits/stdc++.h>
using namespace std;
int solve() {
	int n, a, b;
	cin >> n >> a >> b;
	if(n == 0)
		exit(0);
	vector<pair<int, int>> v;
	for(int i=0; i<n; i++) {
		int k, da, db;
		cin >> k >> da >> db;
		while(k--)
			v.push_back({da, db});
	}
	sort(v.begin(), v.end(), [](pair<int, int> x, pair<int, int> y){return x.first-x.second < y.first-y.second;});
	int total = v.size();
	int mn = max(0, total-b), mx = min(total, a), cur = 0, ans;
	for(int i=0; i<total; i++) {
		cur += v[i].second;
	}
	ans = INT_MAX;
	for(int i=0; i<=mx; i++) {
		if(i) {
			cur -= v[i-1].second;
			cur += v[i-1].first;
		}
		if(i < mn) continue;
		ans = min(ans, cur);
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		cout << solve() << '\n';
	}
}
