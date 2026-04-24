#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	while(cin >> n) {
		if(!n) break;
		int last = -1, t;
		for(int i=0; i<n; i++) {
			cin >> t;
			if(t == last) continue;
			cout << t << ' ';
			last = t;
		}
		cout << "$\n";
	}
}
