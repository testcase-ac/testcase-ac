#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, d;
	cin >> n >> d;
	vector<pair<int, int>> a(n), b(n);
	vector<int> ans(n, INT_MAX);
	set<pair<int, int>, greater<pair<int, int>>> ast, bst;
	queue<int> que;
	for(int i=0; i<n; i++) {
		cin >> a[i].first >> a[i].second;
		if(a[i].second)
			ast.insert({a[i].second, i});
		else {
			que.push(i);
			ans[i] = 1;
		}
	}
	for(int i=0; i<n; i++) {
		cin >> b[i].first >> b[i].second;
		if(b[i].first)
			bst.insert({b[i].first, i});
		else
			que.push(n+i);
	}
	int cur = 2;
	while(que.size()) {
		int s = que.size();
		while(s--) {
			int q = que.front();
			que.pop();
			auto &v = (q < n ? a : b);
			int t = (q < n ? v[q].first : v[q-n].second);
			auto &st = (q < n ? bst : ast);
			auto it = st.lower_bound({t, INT_MAX});
			while(it != st.end() && it->first >= t-d) {
				if(q >= n)
					ans[it->second] = cur;
				que.push(it->second+(q < n ? n : 0));
				it = st.erase(it);
			}
		}
		cur++;
	}
	for(int i=0; i<n; i++) {
		cout << (ans[i] == INT_MAX ? -1 : ans[i]) << '\n';
	}
}
