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
    return Component(na, nb, nc, nd);
  }
  void print() {
    if (c == 0) cout << a << ' ' << b << " 0 0 ";
    else cout << a << ' ' << b << ' ' << c << ' ' << d << ' ';
  }
  Component operator+(Component x) {
    return Component(a * x.a, b * x.a + a * x.b, c * x.a + a * x.c, d).reduce();
  }
  Component operator-(Component x) {
    return Component(a * x.a, b * x.a - a * x.b, c * x.a - a * x.c, d).reduce();
  }
  Component operator*(Component x) {
    return Component(a * x.a, b * x.b + c * x.c * d, c * x.b + b * x.c, d).reduce();
  }
  Component operator/(Component x) {
    return Component(
      a * (x.b * x.b - x.c * x.c * d),
      x.a * (b * x.b - c * x.c * d),
      x.a * (c * x.b - b * x.c),
      d
    ).reduce();
  }
};

class Complex {
  Component real, imag;
public:
  Complex(Component real, Component imag) : real(real), imag(imag) {}
  void print() {
    real.print();
    imag.print();
    cout << '\n';
  }
  Complex operator+(Complex x) {
    Component nreal = (real + x.real).reduce(), nimag = (imag + x.imag).reduce();
    return Complex(nreal, nimag);
  }
  Complex operator-(Complex x) {
    Component nreal = (real - x.real).reduce(), nimag = (imag - x.imag).reduce();
    return Complex(nreal, nimag);
  }
  Complex operator*(Complex x) {
    Component nreal = (real * x.real - imag * x.imag).reduce();
    Component nimag = (real * x.imag + imag * x.real).reduce();
    return Complex(nreal, nimag);
  }
  Complex operator/(Complex x) {
    Component nreal = ((real * x.real + imag * x.imag) / (x.real * x.real + x.imag * x.imag)).reduce();
    Component nimag = ((imag * x.real - real * x.imag) / (x.real * x.real + x.imag * x.imag)).reduce();
    return Complex(nreal, nimag);
  }
};

void solve() {
  ll aa, ab, ac, ad, ae, af, ag, ah, ba, bb, bc, bd, be, bf, bg, bh;
  cin >> aa >> ab >> ac >> ad >> ae >> af >> ag >> ah >> ba >> bb >> bc >> bd >> be >> bf >> bg >> bh;
  Component ar(aa, ab, ac, ad), ai(ae, af, ag, ah), br(ba, bb, bc, bd), bi(be, bf, bg, bh);
  Complex A(ar, ai), B(br, bi);

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
