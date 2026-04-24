#include <bits/stdc++.h>
using namespace std;
int R, C, n;
pair<int, int> pts[10];
char arr[1001][1001];
bool seen[1001][1001];
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int f(pair<int, int> a, pair<int, int> b) {
	memset(seen, 0, sizeof seen);
	int ret = 0;
	queue<pair<int, int>> que({a});
	seen[a.first][a.second] = 1;
	int t = 0;
	while(++t) {
		int s = que.size();
		while(s--) {
			int r, c;
			tie(r,c) = que.front();
			que.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(0 <= tr && tr < R && 0 <= tc && tc < C && !seen[tr][tc] && arr[tr][tc] != 'X') {
					seen[tr][tc] = 1;
					if(make_pair(tr,tc) == b)
						return t;
					que.push({tr,tc});
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C >> n;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'S')
				pts[0] = {i,j};
			else if(isdigit(arr[i][j]))
				pts[arr[i][j]-'0'] = {i,j};
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		ans += f(pts[i], pts[i+1]);
	}
	cout << ans;
}
