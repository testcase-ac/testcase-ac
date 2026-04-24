#include <bits/stdc++.h>
using namespace std;
vector<string> b = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}, f = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
map<string, int> mp;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<10; i++) {
		for(int j=0; j<10; j++) {
			string s = f[i]+b[j];
			mp[s] = i*10+j;
		}
	}
	string s;
	cin >> s;
	sort(s.begin(), s.end());
	string mn;
	int mnval = 1000;
	do {
		auto it = mp.find(s);
		if(it != mp.end() && it->second < mnval) {
			mnval = it->second;
			mn = s;
		}
	} while(next_permutation(s.begin(), s.end()));
	cout << mn;
}
