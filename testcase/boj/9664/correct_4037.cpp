#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, o;
	cin >> n >> o;
	bool ok = 0;
	for(int i=1;; i++) {
		if(i-i/n == o) {
			if(!ok) {
				ok = 1;
				cout << i << ' ';
			}
		} else {
			if(ok) {
				cout << i-1;
				break;
			}
		}
	}
}
