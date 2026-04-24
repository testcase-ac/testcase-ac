#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int lst[MX], init[MX], cur[MX];
// ADGHJ
// CIEEEFFICFIEECEFFB
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> v(m);
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		v[i].resize(t);
		for(int j=0; j<t; j++)
			cin >> v[i][j];
	}
	for(int i=1; i<=n; i++) {
        cin >> lst[i];
		init[i] = lst[i];
	}
	for(int i=m-1; i>=0; i--) {
		int all = 1;
		for(int t: v[i]) {
			if(!init[t]) {
				all = 0;
				break;
			}
		}
		if(!all) {
			for(int t: v[i]) {
				init[t] = 0;
			}
		}
	}
	//printf("init:\n");
	// for(int i=1; i<=n; i++) {
	// 	printf("%d ", cur[i]);
	// }
	// printf("\n");
	memcpy(cur, init, sizeof cur);
	for(int i=0; i<m; i++) {
		int any = 0;
		for(int t: v[i]) {
			if(cur[t]) {
				any = 1;
				break;
			}
		}
		if(any) {
			for(int t: v[i]) {
				cur[t] = 1;
			}
		}
	}
	for(int i=1; i<=n; i++) {
		if(cur[i] != lst[i]) {
			return !(cout << "NO");
		}
	}
	cout << "YES\n";
	for(int i=1; i<=n; i++) {
		cout << init[i] << ' ';
	}
}
