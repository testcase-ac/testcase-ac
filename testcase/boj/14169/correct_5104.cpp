#include <bits/stdc++.h>
using namespace std;
struct point {
	int x, y;
};
const int MX = 1e5+2;
point arr[MX];
bool seen[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, xl, yl, xb, yb;
	cin >> n >> xl >> yl >> xb >> yb;
	map<int, vector<int>> mpx, mpy;
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y;
		mpx[arr[i].x].push_back(i);
		mpy[arr[i].y].push_back(i);
	}
	queue<int> que;
	int cur = 0;
	auto add = [&](point p) {
		if(p.x == xb || p.y == yb) {
			cout << cur;
			exit(0);
		}
		if(mpx[p.x].size()) {
			for(int t: mpx[p.x]) {
				if(!seen[t]) {
					seen[t] = 1;
					que.push(t);
				}
			}
			mpx[p.x].clear();
		}
		if(mpy[p.y].size()) {
			for(int t: mpy[p.y]) {
				if(!seen[t]) {
					seen[t] = 1;
					que.push(t);
				}
			}
			mpy[p.y].clear();
		}
	};
	add({xl, yl});
	while(que.size()) {
		int s = que.size();
		cur++;
		while(s--) {
			int t = que.front();
			que.pop();
			add(arr[t]);
		}
	}
	cout << -1;
}
