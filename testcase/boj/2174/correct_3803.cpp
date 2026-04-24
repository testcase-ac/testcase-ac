#include <bits/stdc++.h>
using namespace std;
int R, C, n, m;
int c2i(char c) {
	switch(c) {
		case 'N': return 0;
		case 'E': return 1;
		case 'S': return 2;
		case 'W': return 3;
	}
	return -1;
}
char lt[] = {'N', 'E', 'S', 'W'};
char i2c(int i) {
	return lt[i];
}
struct Robot {
	int x, y;
	char dir;
	void l() {
		dir = i2c((c2i(dir)+3)%4);
	}
	void r() {
		dir = i2c((c2i(dir)+1)%4);
	}
	bool f() {
		switch(dir) {
			case 'N':
				return ++y <= R;
			case 'E':
				return ++x <= C;
			case 'W':
				return --x >= 1;
			case 'S':
				return --y >= 1;
		}
	}
	bool ateq(Robot &r) {
		return tie(x,y) == tie(r.x, r.y);
	}
};
Robot arr[101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> C >> R >> n >> m;
	for(int i=1; i<=n; i++) {
		cin >> arr[i].x >> arr[i].y >> arr[i].dir;
	}
	while(m--) {
		int i, cnt;
		char dir;
		cin >> i >> dir >> cnt;
		while(cnt--) {
			if(dir == 'L') {
				arr[i].l();
			} else if(dir == 'R') {
				arr[i].r();
			} else if(dir == 'F') {
				if(!arr[i].f())
					return !printf("Robot %d crashes into the wall\n", i);
				for(int j=1; j<=n; j++) {
					if(arr[i].ateq(arr[j]) && i != j)
						return !printf("Robot %d crashes into robot %d\n", i, j);
				}
			}
		}
	}
	printf("OK\n");
}
