#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b;
	while(cin >> a >> b) {
		if(!a && !b) break;
		if(a > b) swap(a, b);
		cout << 2*a-b << '\n';
	}
}
