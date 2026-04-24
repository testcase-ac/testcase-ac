#include <bits/stdc++.h>
using namespace std;
int a, b;
char f(char c) {
	c -= 'A';
	int num = (c * a + b) % 26;
	return (char)(num+'A');
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		cin >> a >> b;
		string s;
		cin >> s;
		for(char c:s) {
			cout << f(c);
		}
		cout << '\n';
	}
}
