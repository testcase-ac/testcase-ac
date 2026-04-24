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
int ans[3];

void solve(vector<vector<int>> &arr, int r, int c, int s) {
	if(s == 1) {
		ans[arr[r][c]]++;
		return;
	}
	int allthis = arr[r][c];
	bool isall = true;
	for(int tr=r; tr<r+s; tr++) {
		for(int tc=c; tc<c+s; tc++) {
			if(arr[tr][tc] != allthis) {
				isall = false;
				goto out;
			}
		}
	}
	out:;
	if(isall) {
		ans[allthis]++;
		return;
	}
	int s3 = s/3;
	rep(i, 3) {
		rep(j, 3) {
			solve(arr, r+i*s3, c+j*s3, s3);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<vector<int>> arr(n, vector<int>(n));
	rep(i, n) rep(j, n) {
		cin >> arr[i][j];
		arr[i][j]++;
	}
	solve(arr,0,0,n);
	cout << ans[0] << '\n' << ans[1] << '\n' << ans[2];
}
