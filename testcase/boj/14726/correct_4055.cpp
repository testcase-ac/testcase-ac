#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		int n = 0;
		for(int i=0; i<s.size(); i++) {
			int t = s[i]-'0';
			if(i%2==0)
				t *= 2;
			if(t >= 10)
				t = (t%10)+(t/10);
			n += t;
		}
		if(n % 10 == 0) cout << "T\n";
		else cout << "F\n";
	}
}
