#include <bits/stdc++.h>
using namespace std;
const int MX = 5000;
int dp[MX][MX], c[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> c[i];
	}
	vector<int> a;
	int j = 0;
	for(int i=0; i<n; i=j) {
		while(j < n && c[i] == c[j]) j++;
		a.push_back(c[i]);
	}
	n = a.size();
	for(int d=1; d<n; d++) {
		for(int l=0; l+d<n; l++) {
			int r = l+d;
			dp[l][r] = INT_MAX;
			for(int k=l; k<r; k++) {
				dp[l][r] = min(dp[l][r], dp[l][k]+dp[k+1][r]+(a[l]!=a[k+1]));
			}
		}
	}
	cout << dp[0][n-1];
}
