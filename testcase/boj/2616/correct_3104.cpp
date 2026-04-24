#include <iostream>
#include <algorithm>
#define rep(i,n) for(int i=0; i<(n); i++)
using namespace std;
#define MAXN 50005
int dp[3][MAXN], a[MAXN];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, k;
	cin >> n;
	rep(i,n) cin >> a[i];
	cin >> k;
	int sum = 0;
	for(int i=n-1; i>=0; i--) {
		if(i + k < n) sum -= a[i+k];
		sum += a[i];
		dp[0][i] = max(sum, dp[0][i+1]);
	}
	sum = 0;
	for(int i=n-1; i>=0; i--) {
		if(i + k < n) sum -= a[i+k];
		sum += a[i];
		if(i + k >= n) continue;
		dp[1][i] = max(sum+dp[0][i+k], dp[1][i+1]);
	}
	sum = 0;
	for(int i=n-1; i>=0; i--) {
		if(i + k < n) sum -= a[i+k];
		sum += a[i];
		if(i + k >= n) continue;
		dp[2][i] = max(sum+dp[1][i+k], dp[2][i+1]);	
	}
	cout << dp[2][0];
}
