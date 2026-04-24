#include <bits/stdc++.h>
using namespace std;

int a[2][2];
void rotate() {
	int temp = a[0][0];
	a[0][0] = a[1][0];
	a[1][0] = a[1][1];
	a[1][1] = a[0][1];
	a[0][1] = temp;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	double maxf = 0;
	int ans = 0;
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			cin >> a[i][j];
		}
	}
	for(int i=0; i<4; i++) {
		double f = (double)a[0][0]/a[1][0] + (double)a[0][1]/a[1][1];
		if(f > maxf) {
			ans = i;
			maxf = f;
		}
		rotate();
	}
	cout << ans;
}
