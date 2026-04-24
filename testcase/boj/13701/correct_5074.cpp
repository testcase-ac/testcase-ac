#include <bits/stdc++.h>
using namespace std;
const int MX = 1<<25;
bitset<MX> bs;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	while(cin >> t) {
		if(bs[t]) continue;
		bs[t] = 1;
		cout << t << ' ';
	}
}
