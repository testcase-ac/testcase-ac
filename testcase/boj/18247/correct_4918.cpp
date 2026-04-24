#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int a, b;
		cin >> a >> b;
		if(a < 12 || b < 4)
			cout << "-1\n";
		else
			cout << 11*b+4 << '\n';
	}
}
