#include <bits/stdc++.h>
using namespace std;
char arr[600][600];
int ans[5];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R*5+1; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			int r = i*5+1, c = j*5+1, k = 0;
			while(arr[r][c] == '*') r++, k++;
			ans[k]++;
		}
	}
	for(int i=0; i<5; i++) {
		cout << ans[i] << ' ';
	}
}
