#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b, n;
	cin >> a >> b >> n;
	a %= b;
	n--;
	while(n--) {
		a *= 10;
		a %= b;
	}
	cout << (a*10)/b;
}
