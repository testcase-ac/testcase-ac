#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b;
	cin >> a >> b;
	a %= 30;
	a *= 12;
	cout << (a == b ? 'O' : 'X');
}
