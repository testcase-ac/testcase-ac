#include <bits/stdc++.h>
using namespace std;

char arr[51][51];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	int rcnt = 0, ccnt = 0;
	for(int i=0; i<R; i++) {
		bool none = true;
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'X') {
				none = false;
				break;
			}
		}
		if(none) rcnt++;
	}
	for(int j=0; j<C; j++) {
		bool none = true;
		for(int i=0; i<R; i++) {
			if(arr[i][j] == 'X') {
				none = false;
				break;
			}
		}
		if(none) ccnt++;
	}
	cout << max(rcnt, ccnt);
}
