#include <iostream>
#include <vector>

#define MOD 1000000007
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
int ans = MOD;
vector<string> arr;
int gr, gc;
bool printed = false;
void reached(int r, int c, bool &flag) {
	if(r == gr && c == gc)
		flag = true;
}
void solve(int t, int rr, int rc, int br, int bc, int lastmove);
void roll(int t, int firstr, int firstc, int secondr, int secondc, int d, bool isfirstred) {
	bool freach = false, sreach = false;
	while(arr[firstr+dr[d]][firstc+dc[d]] != '#') {
		firstr += dr[d];
		firstc += dc[d];
		reached(firstr, firstc, freach);
	}
	while(arr[secondr+dr[d]][secondc+dc[d]] != '#') {
		secondr += dr[d];
		secondc += dc[d];
		reached(secondr, secondc, sreach);
	}
	if(firstr == secondr && firstc == secondc) {
		secondr -= dr[d];
		secondc -= dc[d];
	}
	if(freach || sreach) {
		if(!(isfirstred ? sreach : freach))
			ans = min(ans, t);
	} else {
		if(isfirstred)
			solve(t+1, firstr, firstc, secondr, secondc, d);
		else
			solve(t+1, secondr, secondc, firstr, firstc, d);
	}
}
void solve(int t, int rr, int rc, int br, int bc, int lastmove) {
	if(t == 11)
		return;
	if(lastmove == -1 || lastmove <= 1) { // last move was vertical, now move in horizontal
		if(rc < bc) {
			roll(t, rr, rc, br, bc, 2, true);
			roll(t, br, bc, rr, rc, 3, false);
		} else {
			roll(t, br, bc, rr, rc, 2, false);
			roll(t, rr, rc, br, bc, 3, true);
		}
	}
	if(lastmove == -1 || lastmove >= 2) { // last move was horizontal, now move in vertical
		if(rr < br) {
			roll(t, rr, rc, br, bc, 0, true);
			roll(t, br, bc, rr, rc, 1, false);
		} else {
			roll(t, br, bc, rr, rc, 0, false);
			roll(t, rr, rc, br, bc, 1, true);
		}
	}
}

int main() {
	int R, C;
	cin >> R >> C;
	arr.resize(R);
	rep(i, R) cin >> arr[i];
	int rr, rc, br, bc;
	rep(r, R) {
		rep(c, C) {
			if(arr[r][c] == 'R') {
				rr = r;
				rc = c;
			}
			if(arr[r][c] == 'B') {
				br = r;
				bc = c;
			}
			if(arr[r][c] == 'O') {
				gr = r;
				gc = c;
			}
		}
	}
	solve(1, rr, rc, br, bc, -1);
	cout << (ans == MOD ? -1: ans);
}
