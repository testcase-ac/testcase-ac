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

const int MAX = 40, MOD = 1e9 + 7;
Fraction d[MAX + 1][MAX + 1][MAX + 1];

void solve() {
  int n, K;
  cin >> n >> K;

  d[0][0][0] = 1;
  for (int i = 1; i <= n; i++) for (int j = 0; j <= i; j++) for (int k = 0; j + k <= i; k++) {
    int l = i - j - k;
    Fraction add1 = j > 0 ? (d[i - 1][j - 1][k] / 3) : 0;
    Fraction add2 = k > 0 ? (d[i - 1][j][k - 1] / 3) : 0;
    Fraction add3 = l > 0 ? (d[i - 1][j][k] / 3) : 0;

    d[i][j][k] = d[i][j][k] + add1;
    d[i][j][k] = d[i][j][k] + add2;
    d[i][j][k] = d[i][j][k] + add3;
  }

  Fraction ans = 0;
  for (int i = 1; i <= n; i++) for (int k = 0; k < K; k++) ans = ans + d[i][K][k];
  cout << ans.p << ' ' << ans.q << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
