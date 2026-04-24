#include <bits/stdc++.h>
using namespace std;

int dr[] = {0,1,0,-1}, dc[] = {1,0,-1,0}, R, C, t, ans;
bool arr[100][100];
bool ok(int r, int c) {
	return 0 <= r && r < R && 0 <= c && c < C && !arr[r][c];
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	int r = 0, c = 0;
	while(1) {
		arr[r][c] = 1;
		int tr = r+dr[t], tc = c+dc[t];
		if(!ok(tr, tc)) {
			t = (t+1)%4;
			tr = r+dr[t], tc = c+dc[t];
			if(!ok(tr, tc)) {
				return !(cout << ans);
			}
			ans++;
		}
		r = tr, c = tc;
	}
}
