#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> dp(n, 1e9+7);
	int ans = 0;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		auto it = lower_bound(dp.begin(), dp.end(), t);
		*it = t;
		ans = max(ans, (int)(it-dp.begin()+1));
	}
	cout << ans;
}
