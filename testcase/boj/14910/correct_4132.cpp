#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t, l = -1000000;
	while(cin >> t) {
		if(l > t) return !(cout << "Bad");
		l = t;
	}
	cout << "Good";
}
