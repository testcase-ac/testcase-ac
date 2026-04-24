#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k, n, t = 0;
	cin >> k >> n;
	k--;
	while(n--) {
		int u;
		char c;
		cin >> u >> c;
		t += u;
		if(t >= 210) return !(cout << k+1);
		if(c == 'T') k = (k+1)%8;
	}
}
