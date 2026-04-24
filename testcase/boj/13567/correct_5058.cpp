#include <bits/stdc++.h>
using namespace std;

int dr[] = {0,-1,0,1};
int dc[] = {1,0,-1,0};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int M, n, r = 0, c = 0, dir = 0;
	cin >> M >> n;
	while(n--) {
		string s;
		int d;
		cin >> s >> d;
		if(s == "MOVE") {
			r += dr[dir]*d;
			c += dc[dir]*d;
			if(r < 0 || r > M || c < 0 || c > M)
				return !(cout << -1);
		} else {
			if(d == 0)
				dir = (dir+3)%4;
			else
				dir = (dir+1)%4;
		}
	}
	cout << c << ' ' << r;
}
