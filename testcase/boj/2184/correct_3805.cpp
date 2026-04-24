#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> arr;
int n, L, m;
int dp[1005][1005][2]; // at l/r
int get_rem(int l, int r) {
	return n - (r - l + 1);
}
int weight(int cnt, int from, int to) {
	if(from > to)
		swap(from, to);
	return (n - cnt) * (arr[to] - arr[from]);
}
int f(int l, int r, int t) {
	if(l == m && r == m) {
		return 0;
	}
	int &ret = dp[l][r][t];
	if(ret != -1)
		return ret;
	ret = LLONG_MAX;
	int to = (t ? r : l), cnt = r-l;
	if(l < m) {
		ret = min({ret, f(l+1, r, 0) + weight(cnt, l+1, l) + weight(cnt-1, l, to), f(l+1, r, 1) + weight(cnt, r, l) + weight(cnt-1, l, to)});
	}
	if(r > m) {
		ret = min({ret, f(l, r-1, 0) + weight(cnt, l, r) + weight(cnt-1, r, to), f(l, r-1, 1) + weight(cnt, r-1, r) + weight(cnt-1, r, to)});
	}
	//printf("dp %d, %d, %d = %d\n", l, r, t, ret);
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> L;
	memset(dp, -1, sizeof dp);
	arr.resize(n);
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	arr.push_back(L);
	n++;
	sort(arr.begin(), arr.end());
	m = lower_bound(arr.begin(), arr.end(), L) - arr.begin();
	cout << min(f(0, n-1, 0), f(0, n-1, 1));
}
