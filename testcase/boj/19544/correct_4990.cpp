#include <bits/stdc++.h>
using namespace std;
#define int long long
bitset<500> arr[500];
bool seen[500];
const int MOD = 1e9+7;
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			int t;
			cin >> t;
			arr[i][j] = t;
		}
	}
	int ans = 1;
	for(int i=0; i<n; i++) {
		if(seen[i]) continue;
		if(arr[i].count() == 1)
			continue;
		vector<int> g;
		int poss = 0;
		for(int j=0; j<n; j++) {
			if(i == j) continue;
			if(arr[i] == arr[j]) {
				seen[j] = 1;
				g.push_back(j);
			} else {
				bitset<500> tmp = arr[j];
				tmp[i] = 1;
				if(tmp == arr[i])
					poss++;
			}
		}
		seen[i] = 1;
		if(g.size()) {
			int t = g.size();
			while(t >= 1) {
				ans = ans*t;
				ans %= MOD;
				t--;
			}
		}
		else {
			ans = (ans * poss) % MOD;
		}
	}
	cout << ans;
}
