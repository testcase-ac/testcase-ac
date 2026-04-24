#include <bits/stdc++.h>
using namespace std;
#define int long long
int num[256];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<string> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	int t = 2;
	for(char c='a'; c<='z'; c++) {
		if(c == 'd' || c == 'g' || c == 'j' || c == 'm' || c == 'p' || c == 't' || c == 'w') {
			t++;
		}
		num[c] = t;
	}
	string inp;
	cin >> inp;
	int ans = 0;
	for(string& s: v) {
		if(s.size() != inp.size())
			continue;
		bool ok = 1;
		for(int i=0; i<inp.size(); i++) {
			if(num[s[i]] != inp[i]-'0') {
				ok = 0;
				break;
			}
		}
		if(ok)
			ans++;
	}
	cout << ans;
}
