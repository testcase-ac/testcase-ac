#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int a[3];
	while(n-- > 3) {
		cin >> a[0];
	}
	for(int i=0; i<3; i++) {
		cin >> a[i];
	}
	if(a[2]-a[1] == a[1] -a[0]) {
		cout << a[2] + (a[2]-a[1]);
	} else {
		cout << a[2] * (a[2]/a[1]);
	}
}
