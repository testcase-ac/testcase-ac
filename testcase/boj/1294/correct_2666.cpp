#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<string> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	while(v.size()) {
		sort(v.begin(), v.end(), [](auto &a, auto &b){
			for(int i=0; i<min(a.size(), b.size()); i++) {
				if(a[i] != b[i])
					return a[i] < b[i];
			}
			return a.size() > b.size();
		});
		cout << v[0][0];
		v[0] = v[0].substr(1);
		if(v[0].empty()) {
			v.erase(v.begin());
		}
	}
}
