/*
* 2025 KOI 예선
* 초등부 2번
*/
#include <bits/stdc++.h>
using namespace std;
#define MAX 100'010
int X[100'010];
int Y[100'010];
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int N;
	cin >> N;
	int i;
	int minY = 2e9, maxY = -2e9;
	for (i = 1; i <= N; i++) {
		cin >> X[i] >> Y[i];
		minY = min(minY, Y[i]);
		maxY = max(maxY, Y[i]);
	}
	int ans = 2e9;
	
	int minv = 2e9, maxv = -2e9;
	for (i = 1; i <= N; i++) {
		maxv = max(maxv, X[i] + Y[i]);
		minv = min(minv, X[i] - Y[i]);
	}
	ans = min(ans, (maxv - minY) - (minY + minv));

	minv = 2e9, maxv = -2e9;
	for (i = 1; i <= N; i++) {
		maxv = max(maxv, X[i] - Y[i]);
		minv = min(minv, X[i] + Y[i]);
	}
	ans = min(ans, (maxY + maxv) - (minv - maxY));
	cout << ans;
}