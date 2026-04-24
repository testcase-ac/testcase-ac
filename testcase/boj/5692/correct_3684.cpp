#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	while(1) {
		cin >> s;
		if(s == "0") break;
		reverse(s.begin(), s.end());
		int base = 1, ans = 0;
		for(int i=0; i<s.size(); i++) {
			ans += (s[i]-'0')*base;
			base *= (i+2);
		}
		cout << ans << '\n';
	}
}
