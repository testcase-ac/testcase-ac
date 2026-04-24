#include <bits/stdc++.h>
using namespace std;
pair<int, int> arr[10001];
int dp[10001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	sort(arr+1, arr+n+1);
	for(int i=1; i<=n; i++) {
		dp[i] = dp[i-1]+abs(arr[i].second)*2;
		int cur = abs(arr[i].second)*2;
		for(int j=i-1; j>=1; j--) {
			cur = max({cur, abs(arr[j].second)*2, arr[i].first-arr[j].first});
			dp[i] = min(dp[i], dp[j-1]+cur);
		}
	}
	cout << dp[n];
}
