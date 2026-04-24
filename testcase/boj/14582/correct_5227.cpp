#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a[2][9];
	for(int i=0; i<2; i++) {
		for(int j=0; j<9; j++) {
			cin >> a[i][j];
		}
	}
	int p[2] = {};
	for(int j=0; j<9; j++) {
		for(int i=0; i<2; i++) {
			p[i] += a[i][j];
			if(p[0] > p[1])
				return !(cout << "Yes");
		}
	}
	cout << "No";
}
