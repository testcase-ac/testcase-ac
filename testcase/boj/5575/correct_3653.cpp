#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[3], b[3];
	while(1) {
		for(int i=0; i<3; i++) {
			cin >> a[i];
		}
		for(int i=0; i<3; i++) {
			cin >> b[i];
		}
		if(cin.eof()) break;
		if(a[2] > b[2]) {
			b[2] += 60;
			b[1]--;
		}
		if(a[1] > b[1]) {
			b[1] += 60;
			b[0]--;
		}
		for(int i=0; i<3; i++) {
			cout << b[i]-a[i] << ' ';
		}
		cout << '\n';
	}
}
