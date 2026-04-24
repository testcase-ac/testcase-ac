#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<pair<int, int>> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i].first >> v[i].second;
		if(v[i].first > v[i].second) swap(v[i].first, v[i].second);
	}
	sort(v.begin(), v.end());
	vector<int> arr(n);
	for(int i=0; i<n; i++)
		arr[i] = v[i].second;
	vector<int> dp(n+1, 1e9);
	dp[0] = -1;
	int ans = 0;
	for(int a: arr) {
		int i = upper_bound(dp.begin(), dp.end(), a) - dp.begin();
		dp[i] = min(dp[i], a);
		ans = max(ans, i);
	}
	cout << ans;
}
