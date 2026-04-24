#include <bits/stdc++.h>
using namespace std;
bool seen[6][6];
#define no() return !(cout << "Invalid")
bool ok(string &s, string &p) {
	int a = abs(s[0]-p[0]), b = abs(s[1]-p[1]);
	return (a == 1 && b == 2) || (a == 2 && b == 1);
}
int main() {
	string s, p, start;
	for(int i=0; i<36; i++) {
		cin >> s;
		if(!i) start = s;
		if(!('A' <= s[0] && s[0] <= 'F') || !('1' <= s[1] && s[1] <= '6'))
			no();
		if(i && !ok(s, p)) no();
		bool& b = seen[s[0]-'A'][s[1]-'1'];
		if(b)
			no();
		b = 1;
		p = s;
	}
	if(!ok(start, s)) no();
	cout << "Valid";
}
