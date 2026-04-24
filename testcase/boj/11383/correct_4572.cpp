#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	string a[n], b[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<n; i++) {
		cin >> b[i];
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			if(a[i][j] != b[i][2*j] || a[i][j] != b[i][2*j+1])
				return !(cout << "Not Eyfa");
		}
	}
	cout << "Eyfa";
}
