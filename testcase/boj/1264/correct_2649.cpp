#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	while(1) {
		getline(cin, s);
		if(s == "#") return 0;
		int ans = 0;
		for(char c: s) {
			char t = tolower(c);
			ans += (t=='a' || t=='e' || t=='i' || t=='o' || t=='u');
		}
		cout << ans << '\n';
	}
}
