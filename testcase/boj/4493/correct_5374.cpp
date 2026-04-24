#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, p1 = 0, p2 = 0;
		cin >> n;
		while(n--) {
			char o, t;
			cin >> o >> t;
			if(o == t) continue;
			if(o == 'R' && t == 'S' || o == 'S' && t == 'P' || o == 'P' && t == 'R')
				p1++;
			else
				p2++;
		}
		if(p1 > p2) {
			cout << "Player 1\n";
		} else if(p1 < p2) {
			cout << "Player 2\n";
		} else {
			cout << "TIE\n";
		}
	}
}
