#include <bits/stdc++.h>
using namespace std;

char arr[5][80];
void writeframe(int i, char c) {
	arr[2][i] = arr[1][i+1] = arr[3][i+1] = arr[0][i+2] = arr[4][i+2] = arr[1][i+3] = arr[3][i+3] = arr[2][i+4] = c;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	for(int i=0; i<5; i++) {
		for(int j=0; j<4*n+1; j++) {
			arr[i][j] = '.';
		}
	}
	for(int i=0; i<n; i++) {
		arr[2][2+4*i] = s[i];
	}
	for(int i=0; i<n; i++)
		writeframe(i*4, '#');
	for(int i=2; i<n; i+=3)
		writeframe(i*4, '*');
	for(int i=0; i<5; i++) {
		cout << arr[i] << '\n';
	}
}
