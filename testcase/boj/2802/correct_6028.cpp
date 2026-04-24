#include <bits/stdc++.h>
using namespace std;
int dp[257][257][257];
int arr[257][257][257], K;
bool chk(int m, int &ti, int &tj, int &tk) {
	for(int i=m; i<=256; i++) {
		for(int j=m; j<=256; j++) {
			for(int k=m; k<=256; k++) {
				int v = dp[i][j][k] - dp[i-m][j][k] - dp[i][j-m][k] - dp[i][j][k-m] + dp[i-m][j-m][k] + dp[i-m][j][k-m] + dp[i][j-m][k-m] - dp[i-m][j-m][k-m];
				if(v >= K) {
					ti = i;
					tj = j;
					tk = k;
					return 1;
				}
			}
		}
	}
	return 0;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> K;
	for(int i=0; i<n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a++, b++, c++;
		arr[a][b][c]++;
	}
	for(int i=1; i<=256; i++) {
		for(int j=1; j<=256; j++) {
			for(int k=1; k<=256; k++) {
				dp[i][j][k] = arr[i][j][k] + dp[i-1][j][k] + dp[i][j-1][k] + dp[i][j][k-1] - dp[i-1][j-1][k] - dp[i-1][j][k-1] - dp[i][j-1][k-1] + dp[i-1][j-1][k-1];
			}
		}
	}
	int l = 1, r = 256, ti, tj, tk;
	while(l < r) {
		int m = (l+r) / 2;
		if(chk(m, ti, tj, tk))
			r = m;
		else
			l = m+1;
	}
	chk(l, ti, tj, tk);
	cout << l-1 << '\n';
	int cnt = K;
	for(int i=ti; i>ti-l; i--) {
		for(int j=tj; j>tj-l; j--) {
			for(int k=tk; k>tk-l; k--) {
				while(cnt && arr[i][j][k]) {
					arr[i][j][k]--;
					cnt--;
					cout << i-1 << ' ' << j-1 << ' ' << k-1 << '\n';
				}
			}
		}
	}
}
