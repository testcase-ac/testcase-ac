#include <bits/stdc++.h>
using namespace std;

int grid[50][50], w, h;

inline int isvalid(int r, int c) {
	return 0 <= r && r < h && 0 <= c && c < w;
}
int dr[] = {1,1,1,0,0,-1,-1,-1}, dc[] = {1,0,-1,1,-1,1,0,-1};

void dfs(int r, int c) {
	grid[r][c] = 0;
	for(int i=0; i<8; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(isvalid(tr, tc) && grid[tr][tc])
			dfs(tr, tc);
	}
}

int main() {
	while(1) {
		scanf("%d%d", &w, &h);
		if(!w && !h) break;
		for(int r=0; r<h; r++) {
			for(int c=0; c<w; c++) {
				scanf("%d", &grid[r][c]);
			}
		}
		int ans = 0;
		for(int r=0; r<h; r++) {
			for(int c=0; c<w; c++) {
				if(grid[r][c]) {
					ans++;
					dfs(r, c);
				}
			}
		}
		printf("%d\n", ans);
	}
}
