#include <bits/stdc++.h>
using namespace std;

int n,rb,cb,re,ce,dirb,dire,dr[]={1,-1,0,0},dc[]={0,0,1,-1};
char arr[50][50];
bool seen[50][50][2];
bool in(int l, int x, int r){return l<=x&&x<r;}
bool turnok(int r, int c) {
	if(!in(1,r,n-1) || !in(1,c,n-1)) return false;
	for(int i=r-1; i<=r+1; i++) {
		for(int j=c-1; j<=c+1; j++) {
			if(arr[i][j] == '1') return false;
		}
	}
	return true;
}
bool mvok(int r, int c, int dir) {
	if(dir == 0) {
		if(!in(1,r,n-1) || !in(0,c,n)) return false;
		return arr[r-1][c] == '0' && arr[r][c] == '0' && arr[r+1][c] == '0';
	}
	else {
		if(!in(0,r,n) || !in(1,c,n-1)) return false;
		return arr[r][c-1] == '0' && arr[r][c] == '0' && arr[r][c+1] == '0';
	}
}
struct state {int r, c, d;};
int main() {
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(arr[i][j] == 'B') {
				rb += i, cb += j, arr[i][j] = '0';
				if(j && cb % j)
					dirb = 1;
			} else if(arr[i][j] == 'E') {
				re += i, ce += j, arr[i][j] = '0';
				if(j && ce % j)
					dire = 1;
			}
		}
	}
	rb /= 3, cb /= 3, re /= 3, ce /= 3;
	seen[rb][cb][dirb] = true;
	queue<state> Q;
	Q.push({rb,cb,dirb});
	int t = 0;
	while(!Q.empty()) {
		int s = Q.size();
		while(s--) {
			auto q = Q.front();
			Q.pop();
			int r = q.r, c = q.c, d = q.d;
			if(r == re && c == ce && d == dire)
				return !(cout << t);
			for(int i=0; i<4; i++) {
				int tr = r + dr[i], tc = c + dc[i];
				if(!mvok(tr,tc,d) || seen[tr][tc][d]) continue;
				seen[tr][tc][d] = true;
				Q.push({tr, tc, d});
			}
			if(turnok(r, c) && !seen[r][c][d^1]) {
				seen[r][c][d^1] = true;
				Q.push({r, c, d^1});
			}
		}
		t++;
	}
	cout << 0;
}
