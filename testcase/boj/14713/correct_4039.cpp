#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int)x.size())
vector<string> inputsplit() {
	vector<string> ret;
	string s;
	getline(cin, s);
	int st = 0;
	for(int i=0; i<sz(s); i++) {
		if(s[i] == ' ') {
			ret.push_back(s.substr(st, i-st));
			st = i+1;
		}
	}
	ret.push_back(s.substr(st));
	return ret;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	cin.get();
	int wc = 0;
	vector<string> sentence[n];
	for(int i=0; i<n; i++) {
		sentence[i] = inputsplit();
		wc += sz(sentence[i]);
	}
	vector<string> ref = inputsplit();
	if(wc != sz(ref))
		return !(cout << "Impossible");
	for(auto s: sentence) {
		int i = 0;
		for(auto r: ref) {
			if(i < sz(s) && r == s[i])
				i++;
		}
		if(i < sz(s))
			return !(cout << "Impossible");
	}
	cout << "Possible";
}
