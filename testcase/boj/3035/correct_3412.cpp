#include <bits/stdc++.h>
using namespace std;

char arr[300][300];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c, zr, zc;
	cin >> r >> c >> zr >> zc;
	for(int i=0; i<r; i++) {
		string s;
		cin >> s;
		for(int j=0; j<zr; j++) {
			for(char ch: s) {
				for(int k=0; k<zc; k++) {
					cout << ch;
				}
			}
			cout << '\n';
		}
	}
}
