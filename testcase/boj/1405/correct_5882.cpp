#include <bits/stdc++.h>
using namespace std;

const int MD = 20;
double ans = 1, mvprob[4];
int n;
bool seen[MD*2][MD*2];
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
void dfs(double p, int h, int r, int c) {
	if(seen[r][c]) {
		ans -= p;
		return;
	}
	if(h == n) {
		return;
	}
	seen[r][c] = true;
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		dfs(p*mvprob[i], h+1, tr, tc);
	}
	seen[r][c] = false;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<4; i++) {
		int t;
		cin >> t;
		mvprob[i] = (double)t/100;
	}
	dfs(1,0,MD,MD);
	printf("%.15f", ans);
}
