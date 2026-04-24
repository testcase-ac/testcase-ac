#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string a, b;
	cin >> a >> b;
	int R = b.size(), C = a.size();
	int r, c;
	for(int i=0; i<C; i++) {
		bool ok = false;
		for(int j=0; j<R; j++) {
			if(a[i] == b[j]) {
				r = j;
				c = i;
				ok = true;
				break;
			}
		}
		if(ok) break;
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(i == r) cout << a[j];
			else if(j == c) cout << b[i];
			else cout << '.';
		}
		cout << '\n';
	}
}
