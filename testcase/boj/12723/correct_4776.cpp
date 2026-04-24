#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<n; i++) {
		cin >> b[i];
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	reverse(b.begin(), b.end());
	cout << inner_product(a.begin(), a.end(), b.begin(), 0ll) << '\n';
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	for(int t=1; t<=T; t++) {
		cout << "Case #" << t << ": ";
		solve();
	}
}
