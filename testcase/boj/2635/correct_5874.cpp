#include <bits/stdc++.h>
using namespace std;
vector<int> ans;
void f(int a, int b) {
	vector<int> v = {a, b};
	while(1) {
		int t = v[v.size()-2] - v.back();
		if(t < 0) break;
		v.push_back(t);
	}
	if(ans.size() < v.size()) {
		ans = v;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		f(n, i);
	}
	cout << ans.size() << '\n';
	for(int i=0; i<ans.size(); i++) {
		cout << ans[i] << ' ';
	}
}
