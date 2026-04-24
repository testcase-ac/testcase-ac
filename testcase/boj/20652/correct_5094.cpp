#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e9+7;
struct cow {
	char dir;
	int x, y, mx;
	void init() {
		cin >> dir >> x >> y;
		mx = INF;
	}
	int blocked_at(cow &c) {
		if(dir == c.dir) {
			if(dir == 'E') {
				if(x < c.x && y == c.y)
					return c.x - x;
			} else {
				if(y < c.y && x == c.x)
					return c.y - y;
			}
		} else {
			if(dir == 'E') {
				if(x < c.x && y > c.y && (c.x - x) > (y - c.y) && c.mx >= (y - c.y))
					return c.x - x;
			} else {
				if(y < c.y && x > c.x && (c.y - y) > (x - c.x) && c.mx >= (x - c.x))
					return c.y - y;
			}
		}
		return INF;
	}
};
/*
4,6 5,6 6,6 7,6 8,6 9,6 10,6 11,6
11,2 11,3 11,4 11,5 11,6 11,7,11,8
*/
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<cow> v(n);
	for(int i=0; i<n; i++) {
		v[i].init();
	}
	for(int x=0; x<n; x++) {
		for(int i=0; i<n; i++) {
			int ans = INF;
			for(int j=0; j<n; j++) {
				if(i == j) continue;
				ans = min(ans, v[i].blocked_at(v[j]));
			}
			v[i].mx = ans;
		}
	}
	for(int i=0; i<n; i++) {
		if(v[i].mx == INF) {
			cout << "Infinity\n";
		} else {
			cout << v[i].mx << '\n';
		}
	}
}
