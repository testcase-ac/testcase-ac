#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		int n = s.size();
		if(n&1) {
			for(int i=0; i<n; i++) {
				cout << s[(i*2)%n];
			}
			cout << '\n';
			for(int i=0; i<n; i++) {
				cout << s[(1+i*2)%n];
			}
			cout << '\n';
		} else {
			for(int i=0; i<n; i+=2)
				cout << s[i];
			cout << '\n';
			for(int i=1; i<n; i+=2)
				cout << s[i];
			cout << '\n';
		}
	}
}
