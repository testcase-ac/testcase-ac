#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		char type;
		cin >> n >> type;
		if(type == 'C') {
			char t;
			while(n--) {
				cin >> t;
				cout << (t-'A'+1) << ' ';
			}
			cout << '\n';
		} else {
			int t;
			while(n--) {
				cin >> t;
				cout << (char)(t+'A'-1) << ' ';
			}
			cout << '\n';
		}
	}
}
