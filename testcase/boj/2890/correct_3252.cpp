#include <bits/stdc++.h>
using namespace std;
char arr[50][51];
int ans[10];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	int rank = 1;
	for(int j=C-1; j; j--) {
		int has = 0;
		for(int i=0; i<R; i++) {
			if(isdigit(arr[i][j])) {
				int t = arr[i][j]-'0';
				if(!ans[t]) {
					ans[t] = rank;
					has = 1;
				}
			}
		}
		if(has)
			rank++;
	}
	for(int i=1; i<=9; i++) {
		cout << ans[i] << '\n';
	}
}
