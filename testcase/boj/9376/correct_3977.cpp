#include <bits/stdc++.h>
using namespace std;
const int MX = 101, INF = 0x3f3f3f3f;
char arr[MX][MX];
int dist[3][MX][MX], dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0}, R, C;
struct Info {
	int r, c, d;
	bool operator<(const Info& i) const {
		return d > i.d;
	}
};
void relax(int d[MX][MX]) {
	priority_queue<Info> pq;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(d[i][j] != INF)
				pq.push({i, j, d[i][j]});
		}
	}
	while(!pq.empty()) {
		Info i = pq.top();
		pq.pop();
		if(d[i.r][i.c] > i.d) continue;
		for(int t=0; t<4; t++) {
			int tr = i.r+dr[t], tc = i.c+dc[t];
			if(!(0 <= tr && tr < R && 0 <= tc && tc < C)) continue;
			char c = arr[tr][tc];
			if(c == '.' || c == '$') {
				if(i.d < d[tr][tc]) {
					d[tr][tc] = i.d;
					pq.push({tr,tc,i.d});
				}
			} else if(c == '#'){
				if(i.d+1 < d[tr][tc]) {
					d[tr][tc] = i.d+1;
					pq.push({tr,tc,i.d+1});
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> R >> C;
		vector<pair<int, int>> st;
		for(int i=0; i<R; i++) {
			cin >> arr[i];
			for(int j=0; j<C; j++) {
				if(arr[i][j] == '$')
					st.push_back({i,j});
			}
		}
		memset(dist, 0x3f, sizeof dist);
		for(int i=0; i<2; i++) {
			int r, c;
			tie(r, c) = st[i];
			dist[i][r][c] = 0;
			relax(dist[i]);
		}
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				dist[2][i][j] = min(INF, dist[0][i][j]+dist[1][i][j]-(arr[i][j] == '#'));
			}
		}
		relax(dist[2]);
		int a[3] = {INF,INF,INF};
		for(int k=0; k<3; k++) {
			for(int i=0; i<R; i++) {
				for(int j=0; j<C; j++) {
					if(!(!i || i == R-1 || !j || j == C-1)) continue;
					a[k] = min(a[k], dist[k][i][j]);
				}
			}
		}
		cout << min(a[0]+a[1], a[2]) << '\n';
	}
}
