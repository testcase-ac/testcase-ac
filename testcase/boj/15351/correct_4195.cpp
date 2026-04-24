#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	cin.get();
	while(n--) {
		string s;
		getline(cin, s);
		int t = 0;
		for(char c: s) {
			if(isalpha(c))
				t += c-'A'+1;
		}
		if(t == 100)
			cout << "PERFECT LIFE\n";
		else
			cout << t << '\n';
	}
}
