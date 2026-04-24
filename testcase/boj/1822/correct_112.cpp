#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int a[n], b[m];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<m; i++) {
		cin >> b[i];
	}
	sort(a, a+n);
	sort(b, b+m);
	vector<int> ans;
	for(int i: a) {
		if(!binary_search(b, b+m, i))
			ans.push_back(i);
	}
	cout << ans.size() << '\n';
	for(int i: ans) cout << i << ' ';
}
