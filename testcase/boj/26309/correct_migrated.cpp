//제 코드가 너무 느려서 맞힌 사람 탭 맨 위에 있는 Coxie님의 72465912번 제출 코드를 올립니다
#include <bits/stdc++.h>
using namespace std;
std::ostream& operator<<(std::ostream& o, const __int128_t& x) {
    if (x == std::numeric_limits<__int128_t>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
}
using ull = unsigned long long;
ull modmul(ull a, ull b, ull M) { return (__int128_t)a * b % M; }
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 3; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(),r.end());
	return l;
}

signed main() {
	cin.tie(0)->sync_with_stdio(false);
	ull K;
	cin >> K;
	bool is_odd = true;
	if (K % 2 == 0) {
		K /= 2;
		is_odd = false;
	}
	vector<ull> f = factor(K);
	sort(f.begin(), f.end());
	vector<ull> y;
	function<void(int, ull)> d = [&](int i, ull mul) {
		if (i == (int)f.size()) {
			y.push_back(mul);
			return;
		}
		int j = i;
		while (j < (int)f.size() && f[i] == f[j]) ++j;	
		for (int k = i; k <= j; ++k) {
			d(j, mul);
			mul *= f[i];
		}
	};
	d(0, 1);
	sort(y.begin(), y.end());
	__int128_t p1 = (__int128_t)K * K;
	__int128_t p2 = 1;
	for (int i = 0; i + 1 < (int)y.size(); ++i) {
		__int128_t pp1 = (__int128_t)K / y[i] * y[i + 1];
		__int128_t pp2 = (__int128_t)K / y[i + 1] * y[i];
		if (p1 + p2 > pp1 + pp2) {
			p1 = pp1, p2 = pp2;
		}
	}
	assert(p1 != p2 && p2 < p1);
	if (!is_odd) cout << p2 + K << ' ' << p1 + K << '\n';
	else cout << (p2 + K) / 2 << ' ' << (p1 + K) / 2 << '\n';
	return 0;
}
