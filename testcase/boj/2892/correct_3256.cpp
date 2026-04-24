#include <bits/stdc++.h>
using namespace std;

int h2i(char c) {
	if(isdigit(c))
		return c-'0';
	else
		return c-'A'+10;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	set<int> lows;
	for(int i='a'; i<'z'; i++) {
		for(int j='0'; j<'9'; j++) {
			lows.insert(i^j);
		}
	}
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		int t = h2i(s.back());
		if(s.size() == 2)
			t += h2i(s.front())*16;
		cout << (lows.count(t) ? '-' : '.');	
	}
}
