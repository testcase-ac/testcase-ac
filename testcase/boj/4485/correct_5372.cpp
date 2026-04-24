#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

struct State {
	int cost, x, y;
	bool operator< (const State &s) const{
		return cost > s.cost;
	}
};
int n, grid[125][125], dist[125][125];
int dx[] = {1,-1,0,0}, dy[] = {0,0,1,-1};
inline bool isvalid(int i, int j) {
	return 0 <= i && i < n && 0 <= j && j < n;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	for(int p=1;;p++) {
		cin >> n;
		if(!n) break;
		rep(i,n) rep(j,n) {
			cin >> grid[i][j];
			dist[i][j] = MOD;
		}
		dist[0][0] = grid[0][0];
		priority_queue<State> pq;
		pq.push({grid[0][0], 0, 0});
		while(!pq.empty()) {
			State s = pq.top();
			pq.pop();
			if(s.x == n-1 && s.y == n-1) {
				cout << "Problem " << p << ": " << s.cost << '\n';
				break;
			}
			rep(i,4) {
				int tx = s.x+dx[i], ty = s.y+dy[i];
				if(isvalid(tx,ty) && s.cost+grid[tx][ty] < dist[tx][ty]) {
					dist[tx][ty] = s.cost+grid[tx][ty];
					pq.push({dist[tx][ty], tx, ty});
				}
			}
		}
	}
}
