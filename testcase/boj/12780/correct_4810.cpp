#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s, p;
	cin >> s >> p;
	int ans = 0;
	if(s.size() < p.size()) return !(cout << 0);
	for(int i=0; i<=s.size()-p.size(); i++) {
		bool ok = true;
		for(int j=0; j<p.size(); j++) {
			if(s[i+j] != p[j]) {
				ok = false;
				break;
			}
		}
		ans += ok;
	}
	cout << ans;
}
