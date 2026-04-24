#include <bits/stdc++.h>
using namespace std;

bool isvowel(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	getline(cin, s);
	int i = 0;
	while(i < s.size()) {
		if(i-1>=0 && i+1<s.size() && isvowel(s[i-1]) && s[i-1] == s[i+1] && s[i] == 'p') {
			if(i+2 < s.size())
				cout << s[i+2];
			i += 3;
		}
		else {
			cout << s[i];
			i++;
		}
	}
}
