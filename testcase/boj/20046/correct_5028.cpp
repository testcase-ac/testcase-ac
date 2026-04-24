#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1002;
int arr[MX][MX], dist[MX][MX], dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
struct foo {
	int r, c, w;
	bool operator<(const foo &f) const {
		return w > f.w;
	}
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cin >> arr[i][j];
		}
	}
	memset(dist, 0x3f, sizeof dist);
	priority_queue<foo> pq;
	if(arr[0][0] == -1)
		return !(cout << -1);
	pq.push({0,0,0});
	dist[0][0] = arr[0][0];
	while(pq.size()) {
		auto [r, c, w] = pq.top();
		pq.pop();
		if(w > dist[r][c])
			continue;
		for(int i=0; i<4; i++) {
			int tr = r+dr[i], tc = c+dc[i];
			if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[tr][tc] != -1) {
				if(dist[tr][tc] > dist[r][c] + arr[tr][tc]) {
					dist[tr][tc] = dist[r][c] + arr[tr][tc];
					pq.push({tr, tc, dist[tr][tc]});
				}
			}
		}
	}
	// for(int i=0; i<R; i++) {
	// 	for(int j=0; j<C; j++) {
	// 		printf("%d ", dist[i][j]);
	// 	}
	// 	printf("\n");
	// }
	if(dist[R-1][C-1] == dist[MX-1][MX-1]) {
		cout << -1;
	} else {
		cout << dist[R-1][C-1];
	}
}
