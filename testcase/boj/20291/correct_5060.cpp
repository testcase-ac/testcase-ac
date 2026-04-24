#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	map<string, int> mp;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		string lst = s.substr(s.find_last_of('.')+1);
		mp[lst]++;
	}
	for(auto &pr: mp) {
	cout << pr.first << ' ' << pr.second << '\n';	
	}
}
