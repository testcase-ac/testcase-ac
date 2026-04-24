#include <iostream>
#include <cassert>

#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
#define MAXN 50
int n, m, r, c, d;
int arr[MAXN][MAXN];
int tLeft(int i, int times) {
	if(times == 1) {
		if(i == 0) return 3;
		else return i-1;		
	} else {
		return tLeft(tLeft(i, 1), times-1);
	}

}
inline bool goable(int r, int c, int d) {
	if(d == 0) return r > 0 && arr[r-1][c] == 0;
	if(d == 1) return c < m - 1 && arr[r][c+1] == 0;
	if(d == 2) return r < n - 1 && arr[r+1][c] == 0;
	if(d == 3) return c > 0 && arr[r][c-1] == 0;
	return false;
}

inline bool notWall(int r, int c, int d) {
	if(d == 0) return r > 0 && arr[r-1][c] != 1;
	if(d == 1) return c < m - 1 && arr[r][c+1] != 1;
	if(d == 2) return r < n - 1 && arr[r+1][c] != 1;
	if(d == 3) return c > 0 && arr[r][c-1] != 1;
	return false;
}

inline int goR(int r, int d) {
	if(d == 0) return r-1;
	if(d == 2) return r+1;
	else return r;
}

inline int goC(int c, int d) {
	if(d == 1) return c+1;
	if(d == 3) return c-1;
	else return c;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n >> m >> r >> c >> d;
	rep(i, n) rep(j, m) cin >> arr[i][j];
	int ans = 1;
    assert(!arr[r][c]);
	arr[r][c] = 2;
	while(1) {
		bool movedAndCleaned = false;
		for(int t=1; t<=4; t++) {
			if(goable(r,c,tLeft(d,t))) {
				d = tLeft(d, t);
				r = goR(r, d);
				c = goC(c, d);
				arr[r][c] = 2;
				ans++;
				movedAndCleaned = true;
				break;
			}
		}
		if(movedAndCleaned) continue;
		if(notWall(r,c,tLeft(d, 2))) {
			d = tLeft(d, 2);
			r = goR(r, d);
			c = goC(c, d);
			d = tLeft(d, 2);
		} else {
			return !(cout << ans);
		}
	}
}
