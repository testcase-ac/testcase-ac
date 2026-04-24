#include <bits/stdc++.h>
using namespace std;

char a[30][30][30];
bool seen[30][30][30];
int dh[] = {1,-1,0,0,0,0}, dr[] = {0,0,1,-1,0,0}, dc[] = {0,0,0,0,1,-1};
struct Point {
	int h, r, c;
	bool operator== (Point &p) {
		return h == p.h && r == p.r && c == p.c;
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		memset(seen, 0, sizeof seen);
		int l, r, c;
		cin >> l >> r >> c;
		if(!l) return 0;
		Point start, end;
		for(int i=0; i<l; i++) {
			for(int j=0; j<r; j++) {
				string s;
				cin >> s;
				for(int k=0; k<c; k++) {
					a[i][j][k] = s[k];
					if(s[k] == 'S') {
						start = {i,j,k};
						seen[i][j][k] = true;
					}
					else if(s[k] == 'E')
						end = {i,j,k};
				}
			}
		}
		auto isvalid = [&](int i, int j, int k) {
			return 0 <= i && i < l && 0 <= j && j < r && 0 <= k && k < c;
		};
		queue<Point> que;
		que.push(start);
		int t = 0;
		while(!que.empty()) {
			int s = (int)que.size();
			while(s--) {
				Point p = que.front();
				if(p == end) {
					cout << "Escaped in " << t << " minute(s).\n";
					goto nexttc;
				}
				que.pop();
				for(int i=0; i<6; i++) {
					int th = p.h+dh[i], tr = p.r+dr[i], tc = p.c+dc[i];
					if(isvalid(th, tr, tc) && !seen[th][tr][tc] && a[th][tr][tc] != '#') {
						seen[th][tr][tc] = true;
						que.push({th, tr, tc});
					}
				}
			}
			t++;
		}
		cout << "Trapped!\n";
		nexttc:;
	}
}
