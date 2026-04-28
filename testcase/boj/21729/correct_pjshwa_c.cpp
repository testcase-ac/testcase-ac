#include <iostream>
#include <algorithm>
using namespace std;

long long ft[1000009], rt[1000009], md = 1000003;

long long fp(long long n, long long k)
{
	long long s = 1;
	while (k) {
		if (k & 1LL) s = (s * n) % md;
		n = (n * n) % md; k /= 2;
	}
	return s;
}

long long cb(long long n, long long k)
{
	if (n < k) return 0LL;
	long long s = 1;
	while (n > 0 || k > 0) {
		long long a = n % md, b = k % md; 
		n /= md; k /= md;
		if (a < b) return 0LL;
		long long ss = (ft[a] * rt[b]) % md;
		ss = (ss * rt[a - b]) % md;
		s = (s * ss) % md;
	}
	return s;
}

long long ps(long long n, long long k)
{
	long long ans = cb(n + k - 1LL, k);
	long long t = -1, rk = k - n;
	for (int j = 1; 1LL * j * (3 * j - 1) / 2LL <= k; j++) {
		long long u = 1LL * j * (3 * j - 1) / 2LL;
		long long us = (t * (cb(n + k - u - j - 1LL, n - 1LL) + cb(n + k - u - 1LL, n - 1LL))) % md;
		ans = (ans + us) % md;
		t *= -1;
	}
	ans = (ans + md) % md;
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);	
	cin.tie(0);
	ft[0] = 1;
	for (int i = 1; i < md; i++)
		ft[i] = (ft[i - 1] * i) % md;
	rt[md - 1LL] = fp(ft[md - 1LL], md - 2LL);
	for (int i = md - 2; i >= 0; i--)
		rt[i] = (rt[i + 1] * (i + 1)) % md;
	int tc; cin >> tc;
	for (int ti = 0; ti < tc; ti++) {
		long long n, k; cin >> n >> k;
		if (k <= n) cout << ps(n, k) << '\n';
		else cout << (ps(n, k) + ps(n + 1LL, k - n - 1LL)) % md << '\n';
	}
	return 0;
}
