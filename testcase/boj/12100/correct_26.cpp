#include <bits/stdc++.h>

#define vvi vector<vi>
#define vi vector<int>
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
int n;
vvi rotatearr(vvi &arr) {
	vvi ret(n, vi(n));
	rep(i, n) rep(j, n) ret[i][j] = arr[n-1-j][i];
	return ret;
}
int solve(vvi arr, int moves) {
	if(moves == 5) {
		int ret = 0;
		rep(i, n) rep(j, n) ret = max(ret, arr[i][j]);
		return ret;
	}
	auto arrcpy = arr;
	int ans = 0;
	rep(d, 4) {
		rep(c, n) {
			int top = -1; // the position of "wall" (ie max(wall,merged block, unmergeble block))
			rep(r, n) {
				if(arr[r][c] == 0) continue;
				if(top + 1 == r) continue;
				if(arr[top+1][c] == 0) {
					arr[top+1][c] = arr[r][c];
					arr[r][c] = 0;
				} else if(arr[top+1][c] == arr[r][c]) {
					arr[top+1][c] *= 2;
					arr[r][c] = 0;
					top++;
				} else {
					arr[top+2][c] = arr[r][c];
					if(top+2 != r) arr[r][c] = 0;
					top++;
				}
			}
		} 
		int tempans = solve(arr, moves+1);
		ans = max(ans, tempans);
		arrcpy = rotatearr(arrcpy);
		arr = arrcpy;
	}
	return ans;
}

int main() {
	cin >> n;
	vvi arr(n, vi(n));
	rep(i, n) rep(j, n) cin >> arr[i][j];
	cout << solve(arr, 0);
}