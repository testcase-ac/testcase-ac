#include <bits/stdc++.h>
using namespace std;


int main() {
	int n;
	cin >> n;
	while(n--) {
		string a, b;
		cin >> a >> b;
		int ca[26] = {}, cb[26] = {};
		for(char c: a) {
			assert(islower(c));
			ca[c-'a']++;
		}
		for(char c: b) {
			assert(islower(c));
			cb[c-'a']++;
		}
		bool ok = true;
		for(int i=0; i<26; i++) {
			if(ca[i] != cb[i]) {
				ok = false;
				break;
			}
		}
		if(ok)
			printf("%s & %s are anagrams.\n", a.c_str(), b.c_str());
		else
			printf("%s & %s are NOT anagrams.\n", a.c_str(), b.c_str());
	}	
}
