#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		string s;
		getline(cin, s);
		if(s == "*") break;
		int a[26] = {0};
		for(char c: s) {
			if(isalpha(c))
				a[c-'a']++;
		}
		bool ok = true;
		for(int i=0; i<26; i++) {
			if(!a[i]) {
				ok = false;
				break;
			}
		}
		cout << (ok ? "Y\n" : "N\n");
	}
}
