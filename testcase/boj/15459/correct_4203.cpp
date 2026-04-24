#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int fl[MX], sp[MX], acc[MX];

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		cin >> fl[i] >> sp[i];
		acc[i] = acc[i-1]+fl[i];
	}
	multiset<int> ms;
	int r = 0, sum = 0, ans = INT_MAX;
	for(int l=1; l<=n; l++) {
		while(r < n && sum < m) {
			r++;
			sum += fl[r];
			if(l <= r)
				ms.insert(sp[r]);
		}
		if(sum >= m)
			ans = min(ans, *ms.rbegin());
		if(ms.find(sp[l]) != ms.end()) {
			ms.erase(ms.find(sp[l]));
		}
		sum -= fl[l];
	}
	cout << ans;
}
