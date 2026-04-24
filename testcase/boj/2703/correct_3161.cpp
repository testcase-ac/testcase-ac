#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string msg, rule;
		cin.get();
		getline(cin, msg);
		cin >> rule;
		for(char c: msg) {
			if(isalpha(c))
				cout << rule[c-'A'];
			else
				cout << c;
		}
		cout << '\n';
	}
}
