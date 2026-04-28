#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int Z=15'000'000;

bitset<Z+1> b;

const ll mod = int(1e9) + 7;

ll ipow(ll b, ll e) {
	ll ret = 1;
	while (e) {
		if (e&1) {
			(ret *= b) %= mod;
		}
		(b *= b) %= mod;
		e /= 2;
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);


	ll N, M;
	cin >> N >> M;

	ll A = 1;
	for(ll i=2; i<=Z; ++i) {
		if (b[i]) continue;
		for(ll j=i*i; j<=Z; j+=i) b.set(j);
		ll n = N, m = M;
		ll ans = 0;
		while (n >= i && m >= i) {
			ll cn = n / i;
			ll cm = m / i;
			ans += cn * cm;
			n = cn;
			m = cm;
		}
		(A *= ipow(i, ans)) %= mod;
	}

	cout << A << endl;
	return 0;
}
