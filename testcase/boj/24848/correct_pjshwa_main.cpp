#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Fraction {
  ll p, q;
  Fraction(ll a, ll b) : p(q), q(b) {
    ll g = __gcd(a, b);
    p = a / g;
    q = b / g;
  }
  Fraction() : Fraction(0, 1) {}
  Fraction(ll x) : Fraction(x, 1) {}
  Fraction operator +(Fraction &x) {
    return Fraction(p*x.q + q*x.p, q*x.q);
  }
  Fraction operator -(Fraction &x) {
    return Fraction(p*x.q - q*x.p, q*x.q);
  }
  Fraction operator *(Fraction &x) {
    return Fraction(p*x.p, q*x.q);
  }
  Fraction operator /(Fraction &x) {
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

const int MAX = 300;
int s[MAX + 1], v[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> s[i] >> v[i];

  for (int u = 1; u <= n; u++) {
    
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
