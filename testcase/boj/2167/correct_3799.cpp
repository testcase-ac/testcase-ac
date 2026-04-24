#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 300
int arr[MAXN+1][MAXN+1], sum[MAXN+1][MAXN+1];

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	rep(i, n) {
		rep(j, m) cin >> arr[i+1][j+1];
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++)
			sum[i][j] = sum[i][j-1] + arr[i][j];
		for(int j=1; j<=m; j++)
			sum[i][j] += sum[i-1][j];
	}
	int T;
	cin >> T;
	while(T--) {
		int i, j, x, y;
		cin >> i >> j >> x >> y;
		cout << (sum[x][y] - sum[x][j-1] - sum[i-1][y] + sum[i-1][j-1]) << '\n';
	}
}
