#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 501;
int arr[MX][MX], water[MX][MX], dr[] = {1,1,1,0,0,-1,-1,-1}, dc[] = {1,0,-1,1,-1,1,0,-1};
int R, C;
bool inque[MX][MX];
struct foo {
	int r, c, h;
	bool operator<(const foo& f) const {
		return h > f.h;
	}
};
bool ok(int r, int c) {
	return 1 <= r && r <= R && 1 <= c && c <= C;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			cin >> arr[i][j];
			water[i][j] = max(0ll, arr[i][j]);
		}
	}
	int x, y;
	cin >> x >> y;
	int ans = -arr[x][y];
	water[x][y] = arr[x][y];
	priority_queue<foo> pq;
	pq.push({x, y, water[x][y]});
	while(pq.size()) {
		auto [r, c, h] = pq.top();
		pq.pop();
		if(h > water[r][c])
			continue;
		for(int t=0; t<8; t++) {
			int tr = r+dr[t], tc = c+dc[t];
			if(ok(tr, tc) && max(arr[tr][tc], water[tr][tc]) >= water[r][c]) {
				int targ = max(arr[tr][tc], water[r][c]);
				if(water[tr][tc] > targ) {
					ans += water[tr][tc] - targ;
					water[tr][tc] = targ;
					pq.push({tr, tc, targ});
				}
			}
		}
	}
	cout << ans;
}
