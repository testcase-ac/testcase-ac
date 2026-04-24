#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<m; i++) {
		cin >> b[i];
	}
	if(n > m) {
		swap(a, b);
		swap(n, m);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	for(int i=0; i<n; i++) {
		for(int j=i; j<m; j++) {
			dp[i][j] = min(j == i ? INT_MAX : dp[i][j-1], abs(b[j]-a[i])+(i ? dp[i-1][j-1] : 0));
		}
	}
	cout << dp[n-1][m-1];
}
