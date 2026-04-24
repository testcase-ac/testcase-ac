#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int d;
		cin >> d;
		for(int t=1;; t++) {
			if(t+t*t>d) {
				cout << t-1 << '\n';
				break;
			}
		}
	}
}
