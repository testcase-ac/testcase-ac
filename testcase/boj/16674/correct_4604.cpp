#include <bits/stdc++.h>
using namespace std;
int cnt[256];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	for(char c: s)
		cnt[c]++;
	int a = cnt['2'], b = cnt['0'], c = cnt['1'], d = cnt['8'];
	if(a+b+c+d == s.size()) {
		if(a && b && c && d) {
			if(a == b && b == c && c == d)
				cout << 8;
			else
				cout << 2;
		} else cout << 1;
	} else cout << 0;
}
