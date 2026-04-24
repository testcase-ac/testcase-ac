#include <bits/stdc++.h>
using namespace std;

int main() {
	string s, key;
	getline(cin, s);
	cin >> key;
	int i = 0;
	for(char c: s) {
		if(isalpha(c)) {
			int off = key[i] - 'a' + 1;
			printf("%c", (c-'a'+26-off)%26+'a');
		}
		else
			cout << c;
		i = (i+1)%(key.size());
	}
}
