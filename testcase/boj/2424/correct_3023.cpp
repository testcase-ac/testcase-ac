#include <bits/stdc++.h>
using namespace std;
char arr[702][702];
int R, C;
int dist_y[702][702], dist_v[702][702], danger[702][702], dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
bool seen[702][702];
void calc(int dist[][702], int sr, int sc) {
	queue<pair<int, int>> que;
	que.push({sr, sc});
	memset(seen, 0, sizeof seen);
	int d = 0;
	seen[sr][sc] = 1;
	while(que.size()) {
		d++;
		int s = que.size();
		while(s--) {
			auto [r, c] = que.front();
			que.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if((0 <= tr && tr < R && 0 <= tc && tc < C) && arr[tr][tc] != 'I' && !seen[tr][tc]) {
					seen[tr][tc] = 1;
					dist[tr][tc] = d;
					que.push({tr, tc});
				}
			}
		}
	}
}
void calc2(int dist[][702], int sr, int sc) {
	queue<pair<int, int>> que;
	que.push({sr, sc});
	memset(seen, 0, sizeof seen);
	int d = 0;
	seen[sr][sc] = 1;
	while(que.size()) {
		d++;
		int s = que.size();
		while(s--) {
			auto [r, c] = que.front();
			//printf("calc2: visit %d %d\n", r, c);
			que.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if((0 <= tr && tr < R && 0 <= tc && tc < C) && arr[tr][tc] != 'I' && !seen[tr][tc] && d < danger[tr][tc]) {
					seen[tr][tc] = 1;
					dist[tr][tc] = d;
					que.push({tr, tc});
				}
			}
		}
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	int vr, vc, yr, yc, gr, gc;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'V') {
				vr = i, vc = j;
			} else if(arr[i][j] == 'Y') {
				yr = i, yc = j;
			} else if(arr[i][j] == 'T') {
				gr = i, gc = j;
			}
		}
	}
	//calc(dist_y, yr, yc);
	calc(dist_v, vr, vc);
	memset(danger, 0x3f, sizeof danger);
	for(int r=0; r<R; r++) {
		for(int i=0, j=0; i<C; i=j) {
			if(arr[r][j] == 'I') {
				j++;
				continue;
			}
			int mnd = INT_MAX;
			while(j < C && arr[r][j] != 'I') {
				mnd = min(mnd, dist_v[r][j]);
				j++;
			}
			for(int k=i; k<j; k++){
				danger[r][k] = mnd;
			}
		}
	}
	for(int c=0; c<C; c++) {
		for(int i=0, j=0; i<R; i=j) {
			if(arr[j][c] == 'I') {
				j++;
				continue;
			}
			int mnd = INT_MAX;
			while(j < R && arr[j][c] != 'I') {
				mnd = min(mnd, dist_v[j][c]);
				j++;
			}
			for(int k=i; k<j; k++) {
				danger[k][c] = min(danger[k][c], mnd);
			}
		}
	}
/*	printf("danger:\n");
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			printf("%d ", danger[i][j]);
		}
		printf("\n");
	}*/
	calc2(dist_y, yr, yc);
	if(seen[gr][gc])
		cout << "YES\n";
	else
		cout << "NO\n";
}
