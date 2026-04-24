#include <bits/stdc++.h>
using namespace std;
int dr[] = {1,1,1,0,0,-1,-1,-1}, dc[] = {1,0,-1,1,-1,1,0,-1}, R, C;
int arr[251][251];
void dfs(int r, int c) {
	arr[r][c] = 0;
	for(int i=0; i<8; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[tr][tc] == 1)
			dfs(tr, tc);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cin >> arr[i][j];
		}
	}
	int ans = 0;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 1) {
				dfs(i, j);
				ans++;
			}
		}
	}
	cout << ans;
}
