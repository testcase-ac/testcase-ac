#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 500
int arr[MAXN][MAXN];
int days[MAXN][MAXN];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n;
int computeDays(int i, int j) {
	if(days[i][j]) {
		return days[i][j];
	}
	int d = 1;
	rep(k, 4) {
		int x = i+dx[k], y = j+dy[k];
		if(x < n && x >= 0 && y < n && y >= 0 && arr[x][y] > arr[i][j]) {
			d = max(d, computeDays(x, y) + 1);
		}
	}
	days[i][j] = d;
	return d;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	rep(i, n) rep(j, n) cin >> arr[i][j];
	int ans = 0;
	rep(i, n) rep(j, n) ans = max(ans, computeDays(i, j));
	cout << ans;
}
