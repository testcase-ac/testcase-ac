#include <bits/stdc++.h>
using namespace std;

char arr[10][11], ans[10][11];
int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c, ri = 100, re = 0, ci = 100, ce = 0;
	cin >> r >> c;
	for(int i=0; i<r; i++) {
		cin >> arr[i];
	}
	memcpy(ans, arr, sizeof arr);
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			if(arr[i][j] == '.') continue;
			int cnt = 0;
			for(int t=0; t<4; t++) {
				int tr = i+dr[t], tc = j+dc[t];
				if(!(0<=tr && tr<r && 0<=tc && tc<c)) cnt++;
				else if(arr[tr][tc] == '.') cnt++;
			}
			if(cnt >= 3) ans[i][j] = '.';
			else ri = min(ri, i), re = max(re, i), ci = min(ci, j), ce = max(ce, j);
		}
	}
	for(int i=ri; i<=re; i++) {
		for(int j=ci; j<=ce; j++) {
			cout << ans[i][j];
		}
		cout << '\n';
	}
}
