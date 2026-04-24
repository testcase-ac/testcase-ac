#include <bits/stdc++.h>
using namespace std;
const int MX = 4005;
int sq[MX][MX], diag[MX][MX], chk[MX][MX];
void repl(int &a, int b) {
	a = max(a, b);
}
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N;
	for(int i=0; i<N; i++) {
		char c;
		int x, y, a;
		cin >> c >> x >> y >> a;
		x += 2002;
		y += 2002;
		if(c == 'A') {
			sq[x-a/2][y-a/2] = max(sq[x-a/2][y-a/2], a);
		} else {
			a /= 2;
			diag[x-a][y] = max(diag[x-a][y], a);
		}
	}
	int ans = 0;
	for(int x=0; x<MX; x++) {
		for(int y=0; y<MX; y++) {
			if(diag[x][y]) {
				repl(diag[x+1][y+1], diag[x][y]-1);
				repl(diag[x+1][y-1], diag[x][y]-1);
				repl(diag[x+2][y], diag[x][y]-1);
				chk[x][y] |= 1;
				chk[x][y-1] |= 2;
				chk[x+1][y] |= 4;
				chk[x+1][y-1] |= 8;
			}
			if(sq[x][y]) {
				repl(sq[x+1][y], sq[x][y]-1);
				repl(sq[x][y+1], sq[x][y]-1);
				repl(sq[x+1][y+1], sq[x][y]-1);
				chk[x][y] |= 15;
			}
			if(chk[x][y-1] == 15 || (chk[x][y-1] & 9) == 9 || (chk[x][y-1] & 6) == 6) {
				ans += 4;
			} else if(__builtin_popcount(chk[x][y-1]) == 1) {
				ans += 2;
			} else if(chk[x][y-1] == 0) {
				// += 0
			} else {
				ans += 3;
			}
		}

	}

	cout << fixed << setprecision(2) << (ans / 4.0);
}
