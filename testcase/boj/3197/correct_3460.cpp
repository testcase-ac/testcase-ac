#include <bits/stdc++.h>
using namespace std;
char arr[1500][1501];
bool seen[1500][1500];
int par[2250001], R, C, dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, g1=-1, g2;
int findp(int i) {return par[i] == i ? i : par[i] = findp(par[i]);}
void join(int i, int j) {
	i = findp(i), j = findp(j);
	if(i != j)
		par[i] = j;
}
bool ok(int i, int j) {
	return 0 <= i && i < R && 0 <= j && j < C;
}
int to1d(int i, int j) {
	return i*C+j;
}
queue<pair<int, int>> que;
void addpt(int r, int c) {
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(!ok(tr, tc)) continue;
		if(arr[tr][tc] == '.')
			join(to1d(tr, tc), to1d(r, c));
		else if(!seen[tr][tc] && arr[tr][tc] == 'X') {
			seen[tr][tc] = 1;
			que.push({tr, tc});
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<R*C; i++)
		par[i] = i;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'L') {
				(g1 == -1 ? g1 : g2) = i*C+j;
				arr[i][j] = '.';
			}
			if(arr[i][j] == 'X')
				continue;
			addpt(i, j);
		}
	}
	int t = 0;
	while(1) {
		if(findp(g1) == findp(g2))
			return !(cout << t);
		int s = que.size();
		while(s--) {
			int r, c;
			tie(r, c) = que.front();
			arr[r][c] = '.';
			que.pop();
			addpt(r, c);
		}
		t++;
	}
}
