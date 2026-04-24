#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	getline(cin,s);
	int i = 0;
	for(char c: s) {
		if(i == 0 && c == 'U') i++;
		else if(i == 1 && c == 'C') i++;
		else if(i == 2 && c == 'P') i++;
		else if(i == 3 && c == 'C') return !(cout << "I love UCPC");
	}
	cout << "I hate UCPC";
}
