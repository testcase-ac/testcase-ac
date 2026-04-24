#include <bits/stdc++.h>
using namespace std;
const int MX = 1000;
int arr[MX], dp[MX], prv[MX], ind[MX];
void f(int i) {
	if(i == -1) return;
	f(prv[i]);
	cout << arr[i] << ' ';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	memset(dp, 0x3f, sizeof dp);
	int ans = 0;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		int it = lower_bound(dp, dp+n, arr[i]) - dp;
		ans = max(ans, it);
		dp[it] = arr[i];
		ind[it] = i;
		prv[i] = (it ? ind[it-1] : -1);
	}
	cout << ans+1 << '\n';
	f(ind[ans]);
}
