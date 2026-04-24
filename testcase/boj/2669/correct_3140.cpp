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

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	bool arr[100][100]; set0(arr);
	rep(i, 4) {
		int r, c, r2, c2;
		cin >> r >> c >> r2 >> c2;
		for(int i=r;i<r2;i++) {
			for(int j=c;j<c2;j++) {
				arr[i][j] = true;
			}
		}
	}
	int ans = 0;
	rep(i, 100) rep(j, 100) if(arr[i][j]) ans++;
	cout << ans;
}
