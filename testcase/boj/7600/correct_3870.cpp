#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	while(1) {
		getline(cin, s);
		if(s == "#") break;
		set<char> st;
		for(char c: s) {
			if(isalpha(c))
				st.insert(tolower(c));
		}
		cout << st.size() << '\n';
	}
}
