#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}


class Component {
  ll a, b, c, d;
public:
  Component(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {}
  Component reduce() {
    ll na = a, nb = b, nc = c, nd = d;
    ll g = abs(__gcd(na, __gcd(nb, nc))) * (abs(na) / na);
    na /= g, nb /= g, nc /= g;
    if (nc == 0) nd = 0;
    return Component(na, nb, nc, nd);
  }
  void print() {
    cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
  }
  Component operator+(Component &x) {
    return Component(a * x.a, b * x.a + a * x.b, c * x.a + a * x.c, d).reduce();
  }
  Component operator-(Component &x) {
    return Component(a * x.a, b * x.a - a * x.b, c * x.a - a * x.c, d).reduce();
  }
  Component operator*(Component &x) {
    return Component(a * x.a, b * x.b + c * x.c * d, c * x.b + b * x.c, d).reduce();
  }
  Component operator/(Component &x) {
    return Component(
      a * (x.b * x.b - x.c * x.c * d),
      x.a * (b * x.b - c * x.c * d),
      x.a * (c * x.b - b * x.c),
      d
    ).reduce();
  }
};

void solve() {
  ll aa, ab, ac, ad, ba, bb, bc, bd;
  cin >> aa >> ab >> ac >> ad >> ba >> bb >> bc >> bd;

  Component A(aa, ab, ac, ad), B(ba, bb, bc, bd);
  (A + B).print();
  (A - B).print();
  (A * B).print();
  (A / B).print();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
