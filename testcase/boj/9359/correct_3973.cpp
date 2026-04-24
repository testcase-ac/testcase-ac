#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> pf;
ll a, b;
ll f(int d, ll n, bool pos) {
	if(d == pf.size())
		return n == 1 ? 0 : (b/n-(a-1)/n) * (pos ? 1 : -1);
	return f(d+1, n*pf[d], !pos) + f(d+1, n, pos);
}
int main() {
	int T;
	cin >> T;
	for(int t=1; t<=T; t++) {
		ll n;
		cin >> a >> b >> n;
		pf.clear();
		for(ll i=2; i*i<=n; i++) {
			if(n % i == 0) {
				while(n % i == 0)
					n /= i;
				pf.push_back(i);
			}
		}
		if(n > 1)
			pf.push_back(n);
		printf("Case #%d: %lld\n", t, (b-a+1)-f(0, 1, 0));
	}
}
