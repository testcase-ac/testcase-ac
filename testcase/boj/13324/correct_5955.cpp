#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6+2, INF = -123456789;
int a[MX];
struct persistent_pq {
	multiset<int> pq;
	int ptr;
	vector<pair<int, int>> rec;
	persistent_pq() {
		ptr = 0;
	}
	void left_add(int t) {
		rec.push_back({t, *prev(pq.end())});
		pq.insert(t);
		pq.insert(t);
		pq.erase(prev(pq.end()));
	}
	void right_add(int t) {
		rec.push_back({t, INF});
		pq.insert(t);
	}
	void rollback() {
		if(rec.back().second == INF) {
			pq.erase(pq.find(rec.back().first));
		} else {
			auto [a, b] = rec.back();
			pq.insert(b);
			pq.erase(pq.find(a));
			pq.erase(pq.find(a));
		}
		rec.pop_back();
	}
	int top() {
		return *pq.rbegin();
	}
	vector<int> backtrack() {
		vector<int> ret;
		int r = INT_MAX;
		while(pq.size()) {
			if(top() <= r) {
				r = top();
			}
			ret.push_back(r);
			rollback();
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	persistent_pq pq;
	pq.right_add(a[0]);
	int ans = 0;
	for(int i=1; i<n; i++) {
		a[i] -= i;
		if(a[i] < pq.top()) {
			ans += pq.top()-a[i];
			pq.left_add(a[i]);
		} else {
			pq.right_add(a[i]);
		}
	}
	//cout << ans << '\n';
	vector<int> v = pq.backtrack();
	for(int i=0; i<n; i++) {
		cout << v[i]+i << '\n';
	}
}
