#include <bits/stdc++.h>
using namespace std;

pair<int, int> myrotate(pair<int, int> pt, pair<int, int> r, int type) {
	int x, y, rx, ry;
	tie(x,y) = pt, tie(rx,ry) = r;
	int dx = x - rx, dy = y - ry;
	if(type == 1) swap(dx, dy), dx = -dx;
	else if(type == 2) dx = -dx, dy = -dy;
	else if(type == 3) swap(dx,dy), dy = -dy;
	return {rx+dx, ry+dy};
}
vector<pair<int, int>> pattern[11];
bool grid[201][201];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	pattern[0] = {{0,0}, {1,0}};
	for(int i=1; i<=10; i++) {
		pattern[i] = pattern[i-1];
		auto ref = pattern[i-1].back();
		int n = pattern[i].size();
		for(int j=n-2; j>=0; j--)
			pattern[i].push_back(myrotate(pattern[i-1][j], ref, 1));
	}

	int n;
	cin >> n;
	while(n--) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		if(d == 1) d = 3;
		else if(d == 3) d = 1;
		for(auto pr: pattern[g]) {
			auto p = myrotate(pr, {0,0}, d);
			grid[p.first+x][p.second+y] = true;
		}
	}
	int ans = 0;
	for(int i=0; i<=100; i++) {
		for(int j=0; j<=100; j++) {
			if(grid[i][j] && grid[i][j+1] && grid[i+1][j] && grid[i+1][j+1]) ans++;
		}
	}
	cout << ans;
}
