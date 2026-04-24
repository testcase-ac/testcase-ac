#include <bits/stdc++.h>
using namespace std;

char grid[500][501];
int dist[500][500], dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0}, R, C;
bool ok(int r, int c) {
	return 0<=r && r<R && 0<=c && c<C;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int d;
	cin >> R >> C >> d;
	for(int i=0; i<R; i++)
		cin >> grid[i];
	deque<pair<int,int>> que;
	que.push_front({0,0});
	for(int i=0;i<R;i++) {
		for(int j=0; j<C; j++) {
			dist[i][j] = 1e9;
		}
	}
	dist[0][0] = 0;
	while(!que.empty()) {
		int r, c;
		tie(r,c) = que.front();
		que.pop_front();
		for(int i=0; i<4; i++) {
			int tr = r + dr[i], tc = c+dc[i];
			if(!ok(tr,tc) || grid[tr][tc] == '#') continue;
			if(dist[tr][tc] > dist[r][c]) {
				dist[tr][tc] = dist[r][c];
				que.push_front({tr,tc});
			}
		}
		for(int i=0; i<4; i++) {
			int tr, tc;
			if(dr[i]) {
				tr = r+dr[i]*d;
				if(tr<0 || tr>=R) continue;
				for(tc=max(0,c-d+1); tc<min(C,c+d); tc++) {
					if(dist[tr][tc] > dist[r][c]+1) {
						dist[tr][tc] = dist[r][c]+1;
						que.push_back({tr,tc});
					}
				}
			} else {
				tc = c+dc[i]*d;
				if(tc<0 || tc>=C) continue;
				for(tr=max(0,r-d+1);tr<min(R,r+d); tr++) {
					if(dist[tr][tc] > dist[r][c]+1) {
						dist[tr][tc] = dist[r][c]+1;
						que.push_back({tr,tc});
					}
				}
			}
		}
		int tr = abs(r-(R-1)), tc = abs(c-(C-1));
		if(tr <= d && tc <= d && !(tr == d && tc == d)) {
			if(dist[R-1][C-1] > dist[r][c] + 1)
				dist[R-1][C-1] = dist[r][c]+1;
		}
	}
	cout << dist[R-1][C-1];
}
