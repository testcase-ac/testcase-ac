#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	vector<int> v(7);
	for(int i=0; i<7; i++) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	for(int i=0; i<7; i++) {
		for(int j=i+1; j<7; j++) {
			for(int k=j+1; k<7; k++) {
				vector<int> t({v[i], v[j], v[k], v[i]+v[j], v[i]+v[k], v[j]+v[k], v[i]+v[j]+v[k]});
				sort(t.begin(), t.end());
				if(t == v) {
					cout << v[i] << ' ' << v[j] << ' ' << v[k] << '\n';
				}
			} 
		}
	}
}
