#include <bits/stdc++.h>
using namespace std;
int a[100], b[100];
void solve() {
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		v[i] = i+1;
	}
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=n-1; i>=0; i--) {
		if(a[i] >= v.size()) {
			cout << "IMPOSSIBLE\n";
			return;
		}
		b[i] = v[a[i]];
		v.erase(v.begin()+a[i]);
	}
	for(int i=0; i<n; i++) {
		cout << b[i] << ' ';
	}
	cout << '\n';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--)
		solve();
}
