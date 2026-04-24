#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		string a, b;
		cin >> a >> b;
		if(a == "0" && b == "0")
			break;
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		int n = max(a.size(), b.size()), c = 0, ans = 0;
		for(int i=0; i<n; i++) {
			int x = (i < a.size() ? a[i]-'0' : 0), y = (i < b.size() ? b[i]-'0' : 0);
			c = (x+y+c) >= 10;
			if(c) ans++;
		}
		cout << ans << '\n';
	}
}
