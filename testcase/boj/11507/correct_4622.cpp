#include <bits/stdc++.h>
using namespace std;
map<char, int> mp = {{'P',0},{'K',1},{'H',2},{'T',3}};
bool seen[4][13];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	for(int i=0; i<s.size(); i+=3) {
		char c = s[i];
		int t = (s[i+1]-'0')*10+s[i+2]-'0'-1;
		if(seen[mp[c]][t])
			return !(cout << "GRESKA");
		seen[mp[c]][t] = 1;
	}
	for(int i=0; i<4; i++)
		cout << 13-accumulate(seen[i], seen[i]+13, 0) << ' ';
}
