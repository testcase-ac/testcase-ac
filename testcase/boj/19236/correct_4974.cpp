#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i=0; i<n; i++)
struct fish {
	int idx, dir;
	void read() {cin >> idx >> dir;dir--;}
};
#define vvf vector<vector<fish>>
int dr[] = {-1,-1,0,1,1,1,0,-1}, dc[] = {0,-1,-1,-1,0,1,1,1};
bool ok(int r, int c) {
	return 0 <= r && r < 4 && 0 <= c && c < 4;
}
void go(vvf& A, int r, int c) {
	int &d = A[r][c].dir;
	rep(a, 8) {
		int tr = r + dr[d], tc = c + dc[d];
		if(ok(tr, tc) && A[tr][tc].idx != -1) {
			swap(A[tr][tc], A[r][c]);
			return;
		}
		d = (d+1) % 8;
	}
}
int dfs(vvf A, int sr, int sc) {
	rep(i, 16) {
		rep(r, 4) rep(c, 4) {
			if(A[r][c].idx == i+1) {
				go(A, r, c);
				goto nxt;
			}
		}
		nxt:;
	}
	int sd = A[sr][sc].dir, mx = 0;
	rep(a, 3) {
		int nr = sr + dr[sd] * (a+1), nc = sc + dc[sd] * (a+1);
		if(!ok(nr, nc)) break;
		if(!A[nr][nc].idx) continue;
		int eat = A[nr][nc].idx;
		A[nr][nc].idx = -1;
		A[sr][sc].idx = 0;
		mx = max(mx, dfs(A, nr, nc) + eat);
		A[sr][sc].idx = -1;
		A[nr][nc].idx = eat;
	}
	return mx;
}
int main() {
	vvf A(4, vector<fish>(4));
	rep(i, 4) rep(j, 4) A[i][j].read();
	int sc = A[0][0].idx;
	A[0][0].idx = -1;
	cout << dfs(A, 0, 0) + sc;
}
