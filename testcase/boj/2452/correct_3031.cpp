#include <bits/stdc++.h>
using namespace std;
int arr[100][100], dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, R, C;
int seen[100][100], cur;
vector<int> adj[10001];
bool seen2[10001];
void dfs(int r, int c) {
	seen[r][c] = cur;
	//printf("%d,%d is set to %d\n", r, c, cur);
	for(int t=0; t<4; t++) {
		int tr = r+dr[t], tc = c+dc[t];
		if(0 <= tr && tr < R && 0 <= tc && tc < C && !seen[tr][tc] && arr[r][c] == arr[tr][tc]) {
			dfs(tr, tc);
		}
	}
}
int main() {
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++)
			cin >> arr[i][j];
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(!seen[i][j]) {
				cur++;
				dfs(i, j);
			}
		}
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(i && arr[i-1][j] != arr[i][j]) {
				adj[seen[i-1][j]].push_back(seen[i][j]);
				adj[seen[i][j]].push_back(seen[i-1][j]);
			}
			if(j && arr[i][j-1] != arr[i][j]) {
				adj[seen[i][j-1]].push_back(seen[i][j]);
				adj[seen[i][j]].push_back(seen[i][j-1]);
			}
		}
	}
	int ans = INT_MAX;
	queue<int> que;
	for(int i=1; i<=cur; i++) {
		memset(seen2, 0, sizeof seen2);
		int d = 0;
		que.push(i);
		seen2[i] = 1;
		while(1) {
			int s = que.size();
			while(s--) {
				int f = que.front();
				que.pop();
				for(int a: adj[f]) {
					if(!seen2[a]) {
						seen2[a] = 1;
						que.push(a);
					}
				}
			}
			if(que.empty()) {
				break;
			}
			d++;
		}
		ans = min(ans, d);
	}
	//printf("longest dist is %d\n", ans);
	cout << ans;
}
