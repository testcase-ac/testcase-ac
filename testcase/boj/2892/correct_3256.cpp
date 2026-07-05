#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> hex >> t;
		cout << ((t & 64) ? '-' : '.');
	}
}
