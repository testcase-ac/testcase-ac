#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

class Fraction {
  ll p, q;

  void normalize() {
    ll g = gcd(abs(p), abs(q));
    p /= g; q /= g;
    if (q < 0) p = -p, q = -q;
  }

public:
  Fraction(ll p = 0, ll q = 1) : p(p), q(q) {
    normalize();
  }

  const bool operator>=(const Fraction &other) const {
    return p * other.q >= other.p * q;
  }

	friend ostream& operator << (ostream & out, Fraction i) {
    i.normalize();
    if (i.p == 0) out << 0;
    else if (i.q == 1) out << i.p;
    else out << i.p << '/' << i.q;
    return out;
	}
};

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

ll nC2(ll n) {
  return n * (n - 1) / 2;
}

void solve() {
  int p, q, n; cin >> p >> q >> n;
  if (n == 1) return cout << "0\n", void();
  
  cout << "0 1 ";
  ll x = 1, y = 1, ac = 0; Fraction a(p, q);
  for (int k = 3; k <= n; ++k) {
    Fraction xd(nC2(x + 2), nC2(x + 1)), yd(nC2(y + 2), nC2(y + 1));
    if (xd >= yd && xd >= a) ++x;
    else if (yd >= xd && yd >= a) ++y;
    else ++ac;

    ll cur = nC2(x + 1) % MOD * nC2(y + 1) % MOD;
    ll aval = p * lpow(q, MOD - 2, MOD) % MOD;
    cur = (cur * lpow(aval, ac, MOD)) % MOD;
    cout << cur << ' ';
  }

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
