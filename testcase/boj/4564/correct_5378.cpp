#include <bits/stdc++.h>
using namespace std;

int f(int t) {
	cout << t << ' ';
	if(t < 10) return t;
	string s = to_string(t);
	int res = 1;
	for(int i=0; i<s.size(); i++) {
		res *= s[i]-'0';
	}
	return f(res);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	while(1) {
		cin >> t;
		if(!t) break;
		f(t);
		cout << '\n';
	}
}
