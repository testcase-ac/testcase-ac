#include <bits/stdc++.h>
using namespace std;

char arr[1000][1001];
int R, C, dr[]={1,-1,0,0}, dc[]={0,0,1,-1};
bool dfs(int r, int c) {
	if(r == R-1) return true;
	arr[r][c] = '1';
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(0<=tr&&tr<R&&0<=tc&&tc<C && arr[tr][tc] == '0')
			if(dfs(tr, tc))
				return true;
	}
	return false;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<C; i++) {
		if(arr[0][i] == '0')
			if(dfs(0, i))
				return !(cout << "YES");
	}
	cout << "NO";
}
