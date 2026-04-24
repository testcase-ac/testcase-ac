#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b, c;
	cin >> a >> b >> c;
	if(a+b >= 2*c)
		cout << a+b-2*c;
	else
		cout << a+b;
}
