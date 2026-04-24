#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int l, r;
	cin >> l >> r;
	if(!l && !r)
		return !(cout << "Not a moose");
	if(l == r) {
		cout << "Even " << l*2;
	} else {
		cout << "Odd " << max(l, r) * 2;
	}
}
