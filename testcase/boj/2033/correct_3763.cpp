#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, st = 10;
	cin >> n;
	while(n > st) {
		int rm = n % st;
		if(rm >= st/2) {
			n = (n-rm+st);
		} else {
			n -= rm;
		}
		st *= 10;
	}
	cout << n;
}
