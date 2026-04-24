#include <bits/stdc++.h>
using namespace std;

char arr[101][101], ans[101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	int n = s.size(), r, c;
	for(r=n;; r--) {
		if(n%r == 0 && (r <= n/r)) {
			c = n/r;
			break;
		}
	}
	for(int j=0; j<c; j++) {
		for(int i=0; i<r; i++) {
			arr[i][j] = s[j*r+i];
		}
	}
	for(int i=0; i<r; i++) {
		for(int j=0; j<c; j++) {
			ans[i*c+j] = arr[i][j];
		}
	}
	cout << ans;
}
