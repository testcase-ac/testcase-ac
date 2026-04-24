#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+123;
const int MX = 1e6+3;
ll roll[MX], p[MX];
ll get(int l, int r) {
	ll ret = roll[r] - roll[l];
	if(ret < 0)
		ret += MOD;
	ret *= p[MX-r];
	return ret%MOD;
}
int solve(string &s) {
	int n = s.size();
	for(int i=1; i<=n; i++) {
		char c = s[i-1];
		roll[i] = roll[i-1]*29;
		roll[i] += c;
		roll[i] %= MOD;
	}
	for(int i=1; i<=n; i++) {
		if(n % i) continue;
		bool ok = 1;
		for(int j=2*i; j<=n; j+=i) {
			if(get(j-i, j) != get(j-i*2, j-i)) {
				ok = 0;
				break;
			}
		}
		if(ok)
			return n/i;
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	p[0] = 1;
	for(int i=1; i<MX; i++)
		p[i] = (p[i-1]*29)%MOD;
	while(1) {
		string s;
		cin >> s;
		if(s == ".") break;
		cout << solve(s) << '\n';
	}
}
