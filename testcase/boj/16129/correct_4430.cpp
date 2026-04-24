#include <bits/stdc++.h>
using namespace std;

#define ll long long
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int cntpt(vector<vector<char>> &grid, char nxt, int r, int c, int str, int stc) {
	int R = grid.size(), C = grid[0].size();
	int ret = 0;
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(0 <= tr && tr < R && 0 <= tc && tc < C && grid[tr][tc] == nxt && !(tr == str && tc == stc))
			ret++;
	}
	return ret;
}
ll cntgrid(vector<vector<char>> &grid, int Rst, int Ren) {
	int R = grid.size(), C = grid[0].size();
	ll ret = 0;
	for(int r=Rst; r<Ren; r++) {
		for(int c=0; c<C; c++) {
			if(grid[r][c] != '1') continue;
			int a=0, b=0;
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(0 <= tr && tr < R && 0 <= tc && tc < C) {
					if(grid[tr][tc] == '1')
						a += cntpt(grid, '0', tr, tc, r, c);
					else
						b += cntpt(grid, '1', tr, tc, r, c);
				}
			}
			ret += a*b;
		}
	}
	return ret;
}

void fillgrid(vector<vector<char>> &grid) {
	int r = grid.size(), c = grid[0].size();
	int t = 0;
	char seq[] = {'0','1','1','0','1'};
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			grid[i][j] = seq[t++];
			if(t == 5) t = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	int botr = min(R, 5+R%5);
	R -= botr;
	vector<vector<char>> grid(botr, vector<char>(C));
	fillgrid(grid);
	ll ans = cntgrid(grid, 0, botr);
	if(R) {
		while(grid.size() < 15) grid.push_back(vector<char>(C));
		fillgrid(grid);
		ll addi = cntgrid(grid, 5, 10);
		assert(R % 5 == 0);
		ans += addi * R/5;		
	}
	cout << ans;
}
