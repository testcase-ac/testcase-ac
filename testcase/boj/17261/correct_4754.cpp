#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 524288;
int arr[MX], sum[MX], cnt[MX];
int solve(int t) {
	vector<int> v;
	int p = t;
	while(p > 1) {
		v.push_back(p^1);
		p /= 2;
	}
	sort(v.begin(), v.end(), [](int i, int j){return sum[i]*cnt[j] < sum[j]*cnt[i];});
	int ans = (sum[t] + cnt[t] - 1) / cnt[t];
	int s = sum[t], c = cnt[t];
	for(int k: v) {
		s += sum[k];
		c += cnt[k];
		ans = min(ans, (s+c-1)/c);
	}
	return ans;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	for(int i=n; i; i--) {
		sum[i] = arr[i] + sum[2*i] + sum[2*i+1];
		cnt[i] = cnt[2*i] + cnt[2*i+1];
		if(!cnt[i])
			cnt[i] = 1;
	}
	for(int i=1; i<=n; i++) {
		cout << solve(i) << ' ';
	}
}
