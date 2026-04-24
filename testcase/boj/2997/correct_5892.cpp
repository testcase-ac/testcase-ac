#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a[3];
	for(int i=0; i<3; i++) {
		cin >> a[i];
	}
	sort(a, a+3);
	int x = a[1]-a[0], y = a[2] - a[1];
	if(x == y) {
		cout << a[2] + x;
	} else if(x*2 == y) {
		cout << a[1] + x;
	} else if(x == y*2) {
		cout << a[0] + y;
	}
}
