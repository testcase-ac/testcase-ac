#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
vector<int> buk[MX];
int k;
vector<pair<int, int>> v;
bool solve(int d, int &res) {
	v.clear();
	for(int i=1; i<=k; i++) {
		int l = INT_MIN, r = INT_MIN;
		for(auto x: buk[i]) {
			if(r >= x-d) {
				r = x+d;
			} else {
				if(l != INT_MIN) {
					v.push_back({l, r});
				}
				l = x-d;
				r = x+d;
			}
		}
		if(l != INT_MIN)
			v.push_back({l, r});
	}
	sort(v.begin(), v.end());
	priority_queue<int, vector<int>, greater<int>> pq;
	for(auto& pr: v) {
		while(pq.size() && pq.top() < pr.first)
			pq.pop();
		pq.push(pr.second);
		if(pq.size() == k) {
			res = pr.first;
			return 1;
		}
	}
	return 0;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> k >> n;
	for(int i=0; i<n; i++) {
		int x, t;
		cin >> x >> t;
		buk[t].push_back(x);
	}
	for(int i=1; i<=k; i++) {
		sort(buk[i].begin(), buk[i].end());
	}
	int res, l = 0, r = 1000000000;
	while(l < r) {
		int m = (l+r)/2;
		if(solve(m, res)) {
			r = m;
		} else {
			l = m+1;
		}
	}
	solve(l, res);
	cout << res;
}
