#include <bits/stdc++.h>
using namespace std;
const int MX = 50;
int orig[MX][MX], arr[MX][MX], p[10], tr[] = {1,-1,0,0}, tc[] = {0,0,1,-1}, n, m;
bool seen[MX][MX];
vector<pair<int, int>> virus;
int solve() {
	memcpy(arr, orig, sizeof orig);
	queue<pair<int, int>> que;
	for(int i=0; i<virus.size(); i++) {
		if(p[i] == 1) {
			arr[virus[i].first][virus[i].second] = 1;
			que.push(virus[i]);
		}
		arr[virus[i].first][virus[i].second] = 2;
	}
	int t = 0;
	while(que.size()) {
		int s = que.size();
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(!arr[i][j])
					goto cnt;
			}
		}
		return t;
		cnt:;
		while(s--) {
			auto pr = que.front();
			que.pop();
			for(int i=0; i<4; i++) {
				int dr = pr.first+tr[i], dc = pr.second+tc[i];
				if(!(0 <= dr && dr < n && 0 <= dc && dc < n) || arr[dr][dc] == 1) continue;
				arr[dr][dc] = 1;
				que.push({dr, dc});
			}
		}
		t++;
	}
	return INT_MAX;
}

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> orig[i][j];
			if(orig[i][j] == 2)
				virus.push_back({i,j});
		}
	}
	for(int i=0; i<m; i++) {
		p[i] = 1;
	}
	int ans = INT_MAX;
	do {
		ans = min(ans, solve());
	} while(prev_permutation(p, p+virus.size()));
	cout << (ans == INT_MAX ? -1 : ans);
}
