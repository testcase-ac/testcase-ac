#include <bits/stdc++.h>
using namespace std;

char arr[1000][1001];
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int R, C;
bool ok(int i, int j) {
	return 0 <= i && i < R && 0 <= j && j < C;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	queue<pair<int, int>> fire, me;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'J') me.push({i,j});
			else if(arr[i][j] == 'F') fire.push({i,j});
		}
	}
	int t = 0;
	while(++t) {
		int s = fire.size();
		while(s--) {
			int r, c;
			tie(r, c) = fire.front();
			fire.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(!ok(tr, tc) || arr[tr][tc] == 'F' || arr[tr][tc] == '#') continue;
				arr[tr][tc] = 'F';
				fire.push({tr, tc});
			}
		}
		s = me.size();
		while(s--) {
			int r, c;
			tie(r, c) = me.front();
			me.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(!ok(tr, tc)) return !(cout << t);
				if(arr[tr][tc] == 'F' || arr[tr][tc] == '#' || arr[tr][tc] == 'J') continue;
				arr[tr][tc] = 'J';
				me.push({tr, tc});
			}
		}
		if(!me.size())
			return !(cout << "IMPOSSIBLE");
	}
}
