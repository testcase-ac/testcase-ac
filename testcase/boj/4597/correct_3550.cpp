#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		string s;
		cin >> s;
		if(s == "#") break;
		int cnt = 0;
		for(int i=0; i<s.size()-1; i++) {
			if(s[i] == '1') cnt++;
		}
		if((s.back() == 'o') == (cnt % 2)) s.back() = '0';
		else s.back() = '1';
		cout << s << '\n';
	}
}
