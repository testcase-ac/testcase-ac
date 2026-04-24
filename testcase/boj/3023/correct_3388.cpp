#include <bits/stdc++.h>
using namespace std;

char arr[101][101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c;
	cin >> r >> c;
	for(int i=0; i<r; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			arr[i][2*c-1-j] = arr[i][j];
			arr[2*r-1-i][j] = arr[i][j];
			arr[2*r-1-i][2*c-1-j] = arr[i][j];
		}
	}
	int a, b;
	cin >> a >> b;
	arr[a-1][b-1] = (arr[a-1][b-1] == '#' ? '.' : '#');
	for(int i=0; i<2*r; i++) {
		cout << arr[i] << '\n';
	}
}
