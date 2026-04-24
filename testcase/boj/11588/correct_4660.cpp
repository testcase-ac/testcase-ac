#include <bits/stdc++.h>
using namespace std;
#define int long long
int rest[400];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		rest[i] |= (1<<(a-1));
		rest[i] |= (1<<(b-1));
	}
	int ans = 0;
	for(int i=0; i<(1<<n); i++) {
		bool ok = 1;
		for(int j=0; j<m; j++) {
			if((rest[j] & i) == rest[j]) {
				ok = 0;
				break;
			}
		}
		ans += ok;
	}
	cout << ans;
}
