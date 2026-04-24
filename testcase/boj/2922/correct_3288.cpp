#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll p1[11], p2[11], p3[11];
bool isvowel(char c) {
	return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	p1[0] = p2[0] = p3[0] = 1;
	for(int i=1; i<=10; i++) {
		p1[i] = p1[i-1]*21;
		p2[i] = p2[i-1]*5;
		p3[i] = p3[i-1]*20;
	}
	string s, s2;
	cin >> s;
	s2 = s;
	int n = s.size(), m = 0;
	ll ans = 0;
	bool hasl = 0;
	for(int i=0; i<n; i++) {
		if(s[i] == '_') m++;
		else if(s[i] == 'L') hasl = 1;
	}
	for(int i=0; i<(1<<m); i++) {
		int j = 0, ccnt = 0, vcnt = 0;
		for(int k=0; k<n; k++) {
			if(s[k] == '_') {
				s2[k] = (i&(1<<j)) ? 'A' : 'B';
				if(i&(1<<j)) vcnt++;
				else ccnt++;
				j++;
			}
		}
		bool ok = 1;
		for(int k=2; k<n; k++) {
			bool a = isvowel(s2[k-2]), b = isvowel(s2[k-1]), c = isvowel(s2[k]);
			if((a && b && c) || (!a && !b && !c)) {
				ok = 0;
				break;
			}
		}
		if(ok) {
			if(hasl) ans += p1[ccnt] * p2[vcnt];
			else ans += (p1[ccnt] - p3[ccnt]) * p2[vcnt];
		}
	}
	cout << ans;
}
