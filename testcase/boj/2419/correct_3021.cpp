#include <bits/stdc++.h>
using namespace std;
int dp[301][301][2];
int arr[301];
int n, m;
int f(int l, int r, int dir, int rem) {
	if(!rem)
		return 0;
	int& ret = dp[l][r][dir];
	if(ret != -1)
		return ret;
	ret = INT_MAX;
	int cur = dir ? r : l;
	if(l) {
		ret = min(ret, f(l-1, r, 0, rem-1) + rem*(arr[cur]-arr[l-1]));
	}
	if(r < n-1) {
		ret = min(ret, f(l, r+1, 1, rem-1) + rem*(arr[r+1]-arr[cur]));
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	arr[n++] = 0;
	sort(arr, arr+n);
	int st = 0;
	for(int i=0; i<n; i++) {
		if(arr[i] == 0) {
			st = i;
			break;
		}
	}
	int ans = 0;
	for(int i=1; i<n; i++) {
		memset(dp, -1, sizeof dp);
		ans = max(ans, i*m - f(st, st, 0, i));
	}
	cout << ans;
}
