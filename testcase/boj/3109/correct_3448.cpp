#include <bits/stdc++.h>
using namespace std;
char arr[10000][501];
bool seen[10000][500];
int R, C, dr[] = {-1,0,1};
bool dfs(int r, int c) {
	seen[r][c] = 1;
	if(c == C-1) return 1;
	for(int i=0; i<3; i++) {
		int tr = r+dr[i], tc = c+1;
		if(!seen[tr][tc] && arr[tr][tc] == '.') {
			if(dfs(tr, tc))
				return 1;
		}
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	int ans = 0;
	for(int i=0; i<R; i++) {
		ans += dfs(i, 0);
	}
	cout << ans;
}
