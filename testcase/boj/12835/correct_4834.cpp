#include <bits/stdc++.h>
using namespace std;
#define int long long
int cnt[3];
map<int, vector<int>> mp;
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, l, ans = 0;
	cin >> n >> l;
	for(int i=0; i<n; i++) {
		char c;
		int x, dir;
		cin >> c >> x >> dir;
		c -= 'A';
		if(dir) {
			cnt[c]++;
			ans += (l - x);
		} else {
			ans += x + l;
			mp[x].push_back(c);
		}
	}
	for(auto& [x, v]: mp) {
		if(v.size() == 1) {
			cnt[(v[0]+1)%3]++;
		} else {
			for(int t: v)
				cnt[t]++;
		}
	}
	cout << ans << '\n';
	for(int i=0; i<3; i++) {
		cout << cnt[i] << ' ';
	}
}
