#include <bits/stdc++.h>
using namespace std;

int arr[9][9], cnt[9][9][10];
void f(int i, int j, int k, bool inv=false) {
	int d = inv ? -1 : 1;
	for(int t=0; t<9; t++) {
		cnt[i][t][k]+=d;
		cnt[t][j][k]+=d;
	}
	i /= 3;
	j /= 3;
	for(int r=i*3; r<i*3+3; r++) {
		for(int c=j*3; c<j*3+3; c++) {
			cnt[r][c][k]+=d;
		}
	}
}
void rec(int i, int j) {
	if(i == 9) {
		for(int r=0; r<9; r++) {
			for(int c=0; c<9; c++) {
				cout << arr[r][c];
			}
			cout << '\n';
		}
		exit(0);
	}
	if(arr[i][j]) {
		rec(j == 8 ? i+1 : i, (j+1)%9);
	} else {
		for(int t=1; t<=9; t++) {
			if(cnt[i][j][t]) continue;
			f(i, j, t);
			arr[i][j] = t;
			rec(j == 8 ? i+1 : i, (j+1)%9);
			arr[i][j] = 0;
			f(i, j, t, 1);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<9; i++) {
		string s;
		cin >> s;
		for(int j=0; j<9; j++) {
			arr[i][j] = s[j]-'0';
			if(arr[i][j])
				f(i, j, arr[i][j]);
		}
	}
	rec(0, 0);
}