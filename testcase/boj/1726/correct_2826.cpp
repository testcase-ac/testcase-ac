#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
int R, C;
int arr[100][100];
int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
bool seen[100][100][4];
int nextd[] = {2,3,1,0};
struct State {
	int r, c, dir;
	bool operator== (const State &s) const {
		return r == s.r && c == s.c && dir == s.dir;
	}
	void move1() {
		r += dr[dir];
		c += dc[dir];
	}
	bool valid() {
		return 0 <= r && r < R && 0 <= c && c < C && !arr[r][c];
	}
	bool isseen() {
		return seen[r][c][dir];
	}
	void markseen() {
		seen[r][c][dir] = true;
	}
	void turn() {
		dir = nextd[dir];
	}
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> R >> C;
	rep(i,R) rep(j,C) cin >> arr[i][j];
	State ini, fin;
	cin >> ini.r >> ini.c >> ini.dir;
	ini.r--, ini.c--, ini.dir--;
	cin >> fin.r >> fin.c >> fin.dir;
	fin.r--, fin.c--, fin.dir--;
	if(ini == fin) return !(cout << 0);
	queue<State> que;
	que.push(ini);	
	int t = 0;
	while(1) {
		int z = sz(que);
		while(z--) {
			State s = que.front();
			if(s == fin) return !(cout << t);
			State ns = s;
			que.pop();
			for(int k=1; k<=3; k++) {
				ns.move1();
				if(!ns.valid()) break;
				if(!ns.isseen()) {
					ns.markseen();
					que.push(ns);
				}
			}
			ns = s;
			for(int i: {1, 2}) {
				rep(j,i) ns.turn();
				if(!ns.valid()) break;
				if(!ns.isseen()) {
					ns.markseen();
					que.push(ns);
				}
			}
		}
		t++;
	}
}
