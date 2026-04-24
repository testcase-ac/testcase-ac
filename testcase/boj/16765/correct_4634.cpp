#include <bits/stdc++.h>
using namespace std;
const int MX = 1e4+2;
int a[MX], dp[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}
	for(int i=1; i<=n; i++) {
		int mx = 0;
		for(int j=i; j>max(0,i-k); j--) {
			mx = max(mx, a[j]);
			dp[i] = max(dp[i], mx*(i-j+1)+dp[j-1]);
		}
	}
	cout << dp[n];
}
