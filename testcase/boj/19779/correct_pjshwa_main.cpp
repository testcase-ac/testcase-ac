#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a, b;
  cin >> a >> b;
  if (a > b) swap(a, b);

  ll g = __gcd(a, b), l = a / g * b;
  vector<ll> f1s, f2s;
  for (ll i = 1; i * i <= a; i++) {
    if (a % i) continue;

    f1s.push_back(i);
    if (i * i != a) f1s.push_back(a / i);
  }
  for (ll i = 1; i * i <= b; i++) {
    if (b % i) continue;

    f2s.push_back(i);
    if (i * i != b) f2s.push_back(b / i);
  }

  ll ansx = a, ansy = b;
  for (ll f1 : f1s) for (ll f2 : f2s) {
    ll x = f1 * f2, y = (a * b) / x;
    if (x > y) continue;

    if (__gcd(x, y) == g && x / g * y == l) {
      if (y - x < ansy - ansx) ansx = x, ansy = y;
    }
  }
  cout << ansx << ' ' << ansy << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
