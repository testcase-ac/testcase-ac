#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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
  ll N, M;
  cin >> N >> M;

  vector<pair<Fraction, int>> a;
  for (int i = 0; i < N; i++) {
    int wi, vi;
    cin >> wi >> vi;
    a.push_back({Fraction(vi, wi), wi});
  }
  sort(a.begin(), a.end(), [] (pair<Fraction, int> &a, pair<Fraction, int> &b) {
    return a.first < b.first;
  });
  reverse(a.begin(), a.end());

  Fraction ans = 0;
  for (auto& [f, w] : a) {
    if (M >= w) {
      M -= w;
      ans = ans + f * w;
    }
    else {
      ans = ans + f * M;
      break;
    }
  }

  cout << ans.p << '/' << ans.q << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
