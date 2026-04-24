#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;
struct pt{
	int x,y;
	pt(int a,int b){
		x = a, y = b;
	}
};
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int n,m;
inline bool inrng(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	
	cin >> n >> m;
	int arr[n][m];
	bool seen[n][m] = {};
	rep(i,n)rep(j,m) cin >> arr[i][j];
	queue<pt> que, cheeze;
	que.emplace(0,0);
	int t = 0, lastcheeze = 0;
	while(1) {
		while(!que.empty()) {
			pt p = que.front();
			que.pop();
			rep(i,4) {
				int tx = p.x+dx[i], ty = p.y+dy[i];
				if(!inrng(tx,ty)) continue;
				if(!seen[tx][ty]) {
					seen[tx][ty] = true;
					if(arr[tx][ty] == 0) {
						que.emplace(tx,ty);
					}
					else {
						cheeze.emplace(tx,ty);
					}
				}
			}
		}
		if(cheeze.empty()) {
			cout << t << '\n' << lastcheeze;
			return 0;
		}
		lastcheeze = sz(cheeze);
		while(!cheeze.empty()) {
			que.push(cheeze.front());
			arr[cheeze.front().x][cheeze.front().y] = 0;
			cheeze.pop();
		}
		t++;
	}
}
