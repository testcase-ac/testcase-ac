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

const int MAX = 1e5;

void solve() {
  int N, X, K;
  cin >> N >> X >> K;

  vector<pair<Fraction, int>> v;
  for (int i = 0; i < N; i++) {
    int pi;
    cin >> pi;
    v.push_back({Fraction(X * pi, 100), 1});
    v.push_back({Fraction((200 - X) * pi, 100), -1});
  }
  sort(v.begin(), v.end(), [](pair<Fraction, int> a, pair<Fraction, int> b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
  });

  int cur = 0;
  for (auto& [f, d] : v) {
    cur += d;
    if (cur == K) {
      if (f.q == 1) cout << f.p << '\n';
      else cout << f.p << '/' << f.q << '\n';
      return;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
