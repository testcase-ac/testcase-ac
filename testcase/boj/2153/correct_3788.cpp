#include <bits/stdc++.h>
using namespace std;
bool composed[1041];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=2; i<=1040; i++) {
		if(composed[i]) continue;
		for(int j=i*2; j<=1040; j+=i)
			composed[j] = true;
	}
	string s;
	cin >> s;
	int n = 0;
	for(char c: s) {
		if(islower(c)) {
			n += (c-'a'+1);
		} else {
			n += (c-'A'+27);
		}
	}
	cout << (composed[n] ? "It is not a prime word." : "It is a prime word.");
}
