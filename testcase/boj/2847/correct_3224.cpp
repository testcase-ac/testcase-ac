#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
int dp[100][20000], a[100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<20000; j++) {
			dp[i][j] = MOD;
		}
	}
	for(int i=a[0]; i>=0; i--) {
		dp[0][i] = a[0] - i;
	}
	for(int i=1; i<n; i++) {
		int me = MOD;
		for(int j=0; j<a[i]; j++) {
			me = min(me, dp[i-1][j]);
			dp[i][j+1] = me + a[i]-(j+1);
		}
	}
	cout << *min_element(dp[n-1], dp[n-1]+20000);
}
