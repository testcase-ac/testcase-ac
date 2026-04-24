#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b, g;
	cin >> a >> b;
	a = b - a;
	g = __gcd(a, b);
	cout << a/g << ' ' << b/g;
}
