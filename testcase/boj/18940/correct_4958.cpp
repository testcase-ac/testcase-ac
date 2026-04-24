#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e6+2;
int grundy[MX], n = 200;
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	// grundy[1] = grundy[2] = 1;
	// grundy[3] = 2;
	// for(int i=4; i<=n; i++) {
	// 	set<int> st({grundy[i-3], grundy[i-2]});
	// 	for(int j=1; j<i-3; j++) {
	// 		st.insert(grundy[j] ^ grundy[i-3-j]);
	// 	}
	// 	for(int t: st) {
	// 		if(t != grundy[i])
	// 			break;
	// 		grundy[i]++;
	// 	}
	// }
	// for(int i=1; i<=n; i++) {
	// 	cout << grundy[i] << ',';
	// 	if(i % 34 == 0)
	// 		cout << '\n';
	// }
	vector<int> v = {0,1,1,2,0,3,1,1,0,3,3,2,2,4,0,5,2,2,3,3,0,1,1,3,0,2,1,1,0,4,5,2,7,4,0,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,2,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7,4,8,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,9,3,3,0,1,1,3,0,2,1,1,0,4,5,3,7,4,8};
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		if(n >= v.size()) {
			n -= ((n-v.size())/34 + 1) * 34;
		}
		cout << (v[n] ? "Yuto\n" : "Platina\n");

	}
}
