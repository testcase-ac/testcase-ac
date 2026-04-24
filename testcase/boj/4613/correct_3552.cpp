#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	while(1) {
		getline(cin, s);
		if(s == "#") break;
		int ans = 0;
		for(int i=0; i<s.size(); i++) {
			ans += (i+1)*(isalpha(s[i]) ? s[i]-'A'+1 : 0);
		}
		cout << ans << '\n';
	}
}
