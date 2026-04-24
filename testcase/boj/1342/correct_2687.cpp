#include <bits/stdc++.h>
using namespace std;
map<char, int> mp;
vector<pair<char, int>> v;
int ans = 0, n;
void f(int d, int lst=-1) {
	if(d == n) {
		ans++;
		return;
	}
	for(int i=0; i<v.size(); i++) {
		if(v[i].second && i != lst) {
			v[i].second--;
			f(d+1, i);
			v[i].second++;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	n = s.size();
	for(char c: s)
		mp[c]++;
	v = vector<pair<char, int>>(mp.begin(), mp.end());
	f(0);
	cout << ans;
}
