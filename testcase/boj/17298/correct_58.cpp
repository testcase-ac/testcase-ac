// https://www.acmicpc.net/source/15875378
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n), stk;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	vector<int> ans(n);
	for(int i=n-1; i>=0; i--) {
		while(stk.size() && stk.back() <= a[i])
			stk.pop_back();
		ans[i] = (stk.size() ? stk.back() : -1);
		stk.push_back(a[i]);
	}
	for(int t: ans)
		cout << t << ' ';
}
