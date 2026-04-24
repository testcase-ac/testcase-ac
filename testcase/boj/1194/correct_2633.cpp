#include <bits/stdc++.h>
using namespace std;

bool seen[64][50][50];
char grid[50][51];
int R, C, dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
struct Point {
	int z, r, c;
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	Point start;
	for(int i=0; i<R; i++) {
		cin >> grid[i];
		for(int j=0; j<C; j++) {
			if(grid[i][j] == '0')
				start = {0,i,j};
		}
	}
	queue<Point> que;
	int t = 0;
	que.push(start);
	while(!que.empty()) {
		int s = que.size();
		while(s--) {
			Point p = que.front();
			que.pop();
			if(grid[p.r][p.c] == '1')
				return !(cout << t);
			for(int i=0; i<4; i++) {
				int tz = p.z, tr = p.r+dr[i], tc = p.c+dc[i];
				if(tr>=R || tr < 0 || tc>=C || tc < 0 || grid[tr][tc] == '#') continue;
				if(islower(grid[tr][tc])) {
					int num = grid[tr][tc]-'a';
					tz |= (1 << num);
				}
				if(seen[tz][tr][tc]) continue;
				if(isupper(grid[tr][tc])) {
					int num = grid[tr][tc] - 'A';
					if(!(tz&(1<<num))) continue;
				}
				seen[tz][tr][tc] = true;
				que.push({tz,tr,tc});
			}
		}
		t++;
	}
	cout << -1;
}
