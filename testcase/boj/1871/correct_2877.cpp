#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		int a = 0, b = 0;
		for(int i=0; i<3; i++) {
			a *= 26;
			a += (s[i]-'A');
		}
		for(int i=4; i<8; i++) {
			b *= 10;
			b += (s[i]-'0');
		}
		if(abs(a-b) <= 100) cout << "nice\n";
		else cout << "not nice\n";
	}
}
