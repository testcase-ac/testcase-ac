#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;

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

struct Fraction {
  ll p, q;
  Fraction(ll a, ll b) : p(a), q(b) {
    ll g = __gcd(a, b);
    p = a / g;
    q = b / g;
  }
  Fraction() : Fraction(0, 1) {}
  Fraction(ll x) : Fraction(x, 1) {}
  Fraction operator +(Fraction x) {
    return Fraction(p*x.q + q*x.p, q*x.q);
  }
  Fraction operator -(Fraction x) {
    return Fraction(p*x.q - q*x.p, q*x.q);
  }
  Fraction operator *(Fraction x) {
    return Fraction(p*x.p, q*x.q);
  }
  Fraction operator /(Fraction x) {
    return Fraction(p*x.q, q*x.p);
  }
  Fraction operator *(ll x) {
    return Fraction(p*x, q);
  }
  Fraction operator /(ll x) {
    return Fraction(p, q*x);
  }
  bool operator <(Fraction &x) {
    return p*x.q < x.p*q;
  }
  bool operator >(Fraction &x) {
    return p*x.q > x.p*q;
  }
  bool operator <=(Fraction &x) {
    return p*x.q <= x.p*q;
  }
  bool operator >=(Fraction &x) {
    return p*x.q >= x.p*q;
  }
  bool operator ==(Fraction &x) {
    return p*x.q == x.p*q;
  }
  Fraction abs() {
    return Fraction(p > 0 ? p : -p, q > 0 ? q : -q);
  }
};

void solve() {
  int n, k;
  cin >> n >> k;

  vector<tuple<Fraction, int, int>> v;
  for (int i = 0; i < n; i++) {
    int x, c, h;
    cin >> x >> c >> h;
    v.push_back({Fraction(h, c), c, x});
  }
  sort(v.begin(), v.end(), [](tuple<Fraction, int, int> &a, tuple<Fraction, int, int> &b) {
    auto [a1, a2, a3] = a;
    auto [b1, b2, b3] = b;
    if (a1 == b1) {
      if (a2 == b2) return a3 < b3;
      return a2 < b2;
    }
    return a1 > b1;
  });

  for (int i = 0; i < k; i++) cout << get<2>(v[i]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
