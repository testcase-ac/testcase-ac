#include <bits/stdc++.h>
using namespace std;
int arr[101][101], acc[101][101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		arr[a][b] = 1;
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			acc[i][j] = acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1] + arr[i][j];
		}
	}
	int ans = 1e9;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			for(int d=n-j+1;d>=1; d--) {
				if(m % d) continue;
				int h = m / d;
				if(i+h-1 > n) break;
				int t = acc[i+h-1][j+d-1] - acc[i+h-1][j-1] - acc[i-1][j+d-1] + acc[i-1][j-1];
				ans = min(ans, m-t);
			}
		}
	}
	cout << ans;
}
