#include <bits/stdc++.h>
using namespace std;
string ans, inp;
map<string, char> mp;
int cnt(string a, string b) {
	int p = 0;
	for(int i=0; i<6; i++) {
		if(a[i] != b[i])
			p++;
	}
	return p;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> inp;
	mp["000000"] = 'A';
	mp["001111"] = 'B';
	mp["010011"] = 'C';
	mp["011100"] = 'D';
	mp["100110"] = 'E';
	mp["101001"] = 'F';
	mp["110101"] = 'G';
	mp["111010"] = 'H';
	for(int i=0; i<n; i++) {
		string s = inp.substr(i*6,6);
		int mn = 2;
		char cand;
		for(auto &pr: mp) {
			if(cnt(pr.first, s) < mn) {
				mn = cnt(pr.first, s);
				cand = pr.second;
			}
		}
		if(mn == 2)
			return !(cout << i+1);
		else
			ans.push_back(cand);
	}
	cout << ans;
}
