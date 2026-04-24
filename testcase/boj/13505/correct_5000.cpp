#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	int bm = 0;
	for(int t=29; t>=0; t--) {
		int bit = 1 << t;
		bool ok = 0;
		map<int, int> mp;
		for(int x: v) {
			int val = (x & bit) ? 1 : 2;
			if((val | mp[(~x) & bm]) == 3) {
				ok = 1;
				break;
			}
			mp[x & bm] |= val;
		}
		if(ok) {
			bm |= bit;
		}
	}
	cout << bm;
}
