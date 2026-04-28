#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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
  void print() {
    cout << p << " / " << q << endl;
  }
};

void solve() {
  int a, b; cin >> a >> b;

  Fraction ans(1, 1);
  for (int o = 0; o < 2 * a; o++) {
    vector<int> D;
    for (int i = 0; i < b; i++) D.push_back(2 * i * a);
    for (int i = 0; i < a; i++) D.push_back(2 * i * b + o);
    D.push_back(2 * a * b);
    sort(D.begin(), D.end());

    Fraction maxf(0, 1), minf(1, 1);
    for (int i = 0; i < D.size() - 1; i++) {
      Fraction f(D[i + 1] - D[i], 2 * a * b);
      if (f > maxf) maxf = f;
      if (f < minf) minf = f;
    }

    Fraction diff = maxf - minf;
    if (diff < ans) ans = diff;
  }
  ans.print();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
