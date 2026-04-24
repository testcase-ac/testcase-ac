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

#define MAXM 30
ll ans[MAXM+1][MAXM+1];  // ans[i][j]: only those i<=j is used.

ll compute(ll n, ll m) {
	if(n == m || n == 0) return 1;
	if(ans[n][m]) return ans[n][m];
	ll ret = 0;
	for(int i=m-1; i>=n-1; i--) {
		ret += compute(n-1, i);
	}
	ans[n][m] = ret;
	return ret;

}
int main() {
	int T;
	cin >> T;
	while(T--) {
		ll n, m;
		cin >> n >> m;
		cout << compute(n, m) << '\n';
	}
}
