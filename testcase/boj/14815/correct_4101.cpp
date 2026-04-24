#include <bits/stdc++.h>
using namespace std;
#define int long long
int solve() {
	int n, p;
	cin >> n >> p;
	vector<int> cnt(4);
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		t %= p;
		cnt[t]++;
	}
	if(p == 2) {
		return cnt[0] + (cnt[1]+1) / 2;
	} else if(p == 3) {
		int ans = cnt[0];
		int tmp = min(cnt[1], cnt[2]);
		ans += tmp;
		cnt[1] -= tmp;
		cnt[2] -= tmp;
		ans += cnt[1] / 3 + cnt[2] / 3 + (cnt[1] % 3 || cnt[2] % 3);
		return ans;
	} else {
		
	}
}
int32_t main() {
	int t;
	cin >> t;
	for(int i=1; i<=t; i++) {
		printf("Case #%d: %d\n", i, solve());
	}
}
