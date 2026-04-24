#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t = 0, n;
	cin >> n;
	while(n >= 10) {
		int m = 1;
		while(n) {
			m *= (n%10);
			n /= 10;
		}
		n = m;
		t++;
	}
	cout << t;
}
