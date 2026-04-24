#include <bits/stdc++.h>
using namespace std;
int arr[500][500], dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, R, C;
int ansmx, anscnt;
int dfs(int r, int c) {
	arr[r][c] = 0;
	int ret = 1;
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[tr][tc])
			ret += dfs(tr, tc);
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(arr[i][j]) {
				int s = dfs(i, j);
				anscnt++;
				ansmx = max(ansmx, s);
			}
		}
	}
	cout << anscnt << '\n' << ansmx;
}
