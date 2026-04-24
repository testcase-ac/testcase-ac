#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b;
	string c;
	cin >> a >> b >> c;
	cout << ((c.back()-'0')&1 ? a^b:a);
}
