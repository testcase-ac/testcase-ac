#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 20
int n;
int arr[MAXN][MAXN];
int ans = INT_MAX;
bool selected[MAXN];
void solve(int current, int left) {
	if(!left) {
		int sp = 0, nsp = 0;
		rep(i, n) {
			for(int j=i+1; j<n; j++) {
				if(selected[i] && selected[j])
					sp += arr[i][j] + arr[j][i];
				else if(!selected[i] && !selected[j])
					nsp += arr[i][j] + arr[j][i];
			}
		}
		ans = min(ans, abs(sp-nsp));
		return;
	}
	// need left-1 remains. then boundary is [current, n-left+1)
	for(int i=current; i<n-left+1; i++) {
		selected[i] = true;
		solve(i+1, left-1);
		selected[i] = false;
	}
}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	rep(i, n) rep(j, n) cin >> arr[i][j];
	solve(0, n/2);
	cout << ans;
}
