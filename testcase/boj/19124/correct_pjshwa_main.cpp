#include <bits/stdc++.h>
typedef long long ll;
typedef uint32_t u32;
using namespace std;

u32 modpow(u32 a, ll e) {
	if (e == 0) return 1;
	u32 x = modpow(a * a, e >> 1);
	return e & 1 ? x * a : x;
}

u32 C(ll N, ll K) {
	ll trailingZeroes = 0;
	map<u32, int> ivs;
	int accMult = 0;
	for (int i = 0; i < 3; i++) {
		ll x = (i == 0 ? N : i == 1 ? K : N-K);
		int mult = (i == 0 ? 1 : -1);
		while (x > 0) {
			// Include the product (1 * 3 * ... * (x % 2^32)) ^ mult in the answer.
			ivs[(u32)x + 1] += mult;
			accMult += mult;
			x /= 2;
			trailingZeroes += x * mult;
		}
	}

	u32 cur = 0, res = 1, resdiv = 1;
	for (auto pa : ivs) {
		u32 lim = pa.first, ilim = lim / 2;
		// The odd numbers in the range [last lim, lim) get included 'accMult'
		// times in the answer -- 'pa.second' times for the interval ending at
		// 'lim', and also for all larger intervals. We divide by 2 to avoid
		// potential for overflow.
		u32 prod = 1;
		for (; cur < ilim; cur++) {
			prod *= cur * 2 + 1;
		}
		if (accMult > 0) res *= modpow(prod, accMult);
		else resdiv *= modpow(prod, -accMult);
		accMult -= pa.second;
	}

	res *= modpow(2, trailingZeroes);
	res *= modpow(resdiv, (1LL << 31) - 1);
	return res;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;
  cout << C(n, k) << '\n';
}
