#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod;
int tp(__int128 t) {
	t %= mod;
	__int128 f = t;
	t *= t;
	t %= mod;
	t *= f;
	t %= mod;
	return t;
}
void solve() {
	int t, ans = 0, mult = 1;
	cin >> t;
	string s = to_string(t);
	mod = 1;
	for(int i=0; i<s.size(); i++) {
		mod *= 10;
	}
	while(t) {
		for(int i=0; i<=9; i++) {
			if((tp(ans + mult*i) % (mult * 10)) / mult == t % 10) {
				ans += mult*i;
				break;
			}
		}
		t /= 10;
		mult *= 10;
	}
	cout << ans << '\n';
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--)
		solve();
}
