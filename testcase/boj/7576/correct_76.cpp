#include <bits/stdc++.h>
using namespace std;
int arr[1000][1000];
int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> C >> R;
	queue<pair<int, int>> que;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cin >> arr[i][j];
			if(arr[i][j] == 1)
				que.push({i, j});
		}
	}
	int t = 0;
	while(1) {
		int s = que.size();
		while(s--) {
			int r, c;
			tie(r, c) = que.front();
			que.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[tr][tc] == 0) {
					arr[tr][tc] = 1;
					que.push({tr, tc});
				}
			}
		}
		if(que.empty()) break;
		t++;
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(!arr[i][j])
				return !(cout << -1);
		}
	}
	cout << t;
}
