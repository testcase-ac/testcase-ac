#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll, ll>;

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
};

void solve() {
  int N; cin >> N;

  map<int, int> by_x, by_y;
  map<tll, int> by_slope;

  vector<pll> V;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    V.emplace_back(x, y);
    by_x[x]++; by_y[y]++;
  }
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    auto [x1, y1] = V[i]; auto [x2, y2] = V[j];
    if (x1 == x2 || y1 == y2) continue;

    Fraction slope = Fraction(y2 - y1, x2 - x1);
    by_slope[{slope.p, slope.q, x1, y1}]++;
    by_slope[{slope.p, slope.q, x2, y2}]++;
  }

  ll ans1 = 0, ans2 = 0;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    auto [x1, y1] = V[i]; auto [x2, y2] = V[j];
    if (x1 == x2) {
      ans1 += by_y[y1] + by_y[y2] - 2;
    }
    else if (y1 == y2) {
      ans1 += by_x[x1] + by_x[x2] - 2;
    }
    else {
      Fraction slope = Fraction(x1 - x2, y2 - y1);
      if (by_slope.count({slope.p, slope.q, x1, y1})) {
        ans2 += by_slope[{slope.p, slope.q, x1, y1}];
      }
      if (by_slope.count({slope.p, slope.q, x2, y2})) {
        ans2 += by_slope[{slope.p, slope.q, x2, y2}];
      }
    }
  }

  cout << (ans1 + ans2) / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
