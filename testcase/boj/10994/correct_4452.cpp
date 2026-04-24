#include <bits/stdc++.h>
using namespace std;
char arr[500][500];
int main() {
	int n, R;
	cin >> n;
	R = n*4-3;
	for(int i=0; i<R; i++) {
		for(int j=0; j<R; j++) {
			arr[i][j] = ' ';
		}
	}
	for(int i=0; i<R; i+=2) {
		int t = R/2-abs(R/2-i);
		for(int j=t; j<R-t; j++) {
			arr[i][j] = arr[j][i] = '*';
		}
	}
	for(int i=0; i<R; i++) {
		cout << arr[i] << '\n';
	}
}
