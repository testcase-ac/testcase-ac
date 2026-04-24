#include <bits/stdc++.h>
using namespace std;
int arr[100][100];
int dist[3][100][100], n, T, dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
struct info {
	int h, r, c, w;
	bool operator<(info a) const {
		return w > a.w;
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dist, 0x3f, sizeof dist);
	dist[0][0][0] = 0;
	cin >> n >> T;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	priority_queue<info> pq;
	pq.push({0,0,0,0});
	while(pq.size()) {
		auto cur = pq.top();
		pq.pop();
		if(cur.w > dist[cur.h][cur.r][cur.c]) continue;
		for(int t=0; t<4; t++) {
			int th = (cur.h+1)%3, tr = cur.r + dr[t], tc = cur.c+ dc[t];
			if(!(0 <= tr && tr < n && 0 <= tc && tc < n)) continue;
			int w = T+(th ? 0 : arr[tr][tc]);
			if(cur.w+w < dist[th][tr][tc]) {
				dist[th][tr][tc] = cur.w+w;
				pq.push({th, tr, tc, dist[th][tr][tc]});
			}
		}
	}
	cout << min({dist[0][n-1][n-1], dist[1][n-1][n-1], dist[2][n-1][n-1]});
}
