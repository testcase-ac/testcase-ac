#include <bits/stdc++.h>
using namespace std;
int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
char arr[20][20];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	for(int r=0; r<R; r++) {
		for(int c=0; c<C; c++) {
			if(arr[r][c] != '.') continue;
			int cnt = 0;
			for(int i=0; i<4; i++) {
				int tr = r+dr[i], tc = c+dc[i];
				if(0 <= tr && tr < R && 0 <= tc && tc < C && arr[tr][tc] == '.')
					cnt++;
			}
			if(cnt < 2)
				return !(cout << 1);
		}
	}
	cout << 0;
}
