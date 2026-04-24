#include <bits/stdc++.h>
using namespace std;

int dr[] = {1,-1,0,0}, dc[] = {0,0,-1,1};
char grid[100][101];
bool seen[100][100], keys[26];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int R, C;
		cin >> R >> C;
		memset(seen, 0, sizeof seen);
		memset(keys, 0, sizeof keys);
		for(int i=0; i<R; i++)
			cin >> grid[i];
		string s;
		cin >> s;
		if(s[0]!='0') {
			for(char c:s) keys[c-'a'] = true;
		}
		queue<pair<int, int>> que, locked[26];
		int ans = 0;
		auto push = [&](int r, int c) {
			if(grid[r][c] == '*' || seen[r][c]) return;
			seen[r][c] = true;
			if(islower(grid[r][c])) {
				int i = grid[r][c] - 'a';
				keys[i] = true;
				while(!locked[i].empty()) {
					que.push(locked[i].front());
					locked[i].pop();
				}
			}
			if(grid[r][c] == '$') ans++;
			if(!(isupper(grid[r][c]) && !keys[grid[r][c]-'A'])) {
				que.push({r,c});
			} else {
				locked[grid[r][c]-'A'].push({r,c});
			}
		};
		for(int i=0; i<R; i++) {
			push(i,0);
			push(i,C-1);
		}
		for(int i=0; i<C; i++) {
			push(0,i);
			push(R-1,i);
		}
		while(!que.empty()) {
			int r, c;
			tie(r,c) = que.front();
			que.pop();
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(!(0<=tr && tr<R && 0<=tc && tc<C)) continue;
				push(tr,tc);
			}
		}
		cout << ans << '\n';
	}
}
