#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	int st;
	cin >> st;
	if(st == 2) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n/2; j++) {
				swap(a[i][j], a[i][n-1-j]);
			}
		}
	} else if(st == 3) {
		for(int i=0; i<n/2; i++) {
			for(int j=0; j<n; j++)
				swap(a[i][j], a[n-1-i][j]);
		}
	}
	for(string s: a) cout << s << '\n';
}
