#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int ans = 0, base = 1;
		string s;
		cin >> s;
		for(int i=23; i>=0; i--) {
			if(s[i] == '1')
				ans += base;
			base *= 2;
		}
		cout << ans << '\n';
	}
}
