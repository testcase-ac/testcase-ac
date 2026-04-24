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
inline int max(int a, int b) {
	return (a > b ? a : b);
}
inline int max3(int a, int b, int c) {
	return (a > b && a > c ? a : (b > c ? b : c));
}
#define MAXN 100000
int ans[MAXN][3], arr[MAXN][2];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		rep(i, n) cin >> arr[i][0];
		rep(i, n) cin >> arr[i][1];
		ans[0][0] = arr[0][0];
		ans[0][1] = arr[0][1];
		ans[0][2] = 0;
		for(int i=1; i<n; i++) {
			ans[i][0] = max(ans[i-1][1], ans[i-1][2]) + arr[i][0];
			ans[i][1] = max(ans[i-1][0], ans[i-1][2]) + arr[i][1];
			ans[i][2] = max3(ans[i-1][0], ans[i-1][1], ans[i-1][2]);
		}	
		cout << max3(ans[n-1][0], ans[n-1][1], ans[n-1][2]) << '\n';
	}
}
