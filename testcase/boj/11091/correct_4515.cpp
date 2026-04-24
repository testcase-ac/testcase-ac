#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	int n;
	getline(cin, s);
	n = stoi(s);
	while(n--) {
		getline(cin, s);
		bool has[26] = {};
		for(char c: s) {
			if(isalpha(c)) {
				if(isupper(c))
					c = c - 'A' + 'a';
				has[c-'a'] = 1;
			}
		}
		bool ok = 1;
		for(int i=0; i<26; i++)
			if(!has[i]) ok = 0;
		if(ok) cout << "pangram\n";
		else {
			cout << "missing ";
			for(int i=0; i<26; i++)
				if(!has[i]) cout << (char)(i+'a');
			cout << '\n';
		}
	}
}
