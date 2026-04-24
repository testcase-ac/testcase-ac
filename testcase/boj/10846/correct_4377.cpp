#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[2001], acc[2001], n, a, b;
set<int> val[2001];
const int MX = 42;
bool chk(auto it) {
	return it == val[n].end() || *it > b;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> a >> b;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		acc[i] = acc[i-1] + arr[i];
	}
	int bm = (1ll << MX) - 1;
	for(int i=MX-1; i>=0; i--) {
		val[0] = {0};
		bm ^= (1ll << i);
		for(int j=1; j<=n; j++) {
			val[j].clear();
			for(int k=1; k<=j; k++) {
				int v = acc[j] - acc[k-1];
				if((v & bm) != v)
					continue;
				for(int t: val[k-1]) {
					val[j].insert(t+1);
					if(a == 1)
						break;
				}
			}
		}
		if(chk(a == 1 ? val[n].begin() : val[n].lower_bound(a)))
			bm ^= (1ll << i);
	}
	cout << bm;
}
