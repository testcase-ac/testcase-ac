#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n, p, r;
  cin >> n >> p >> r;

  if (r == 0) {
    if (n < p) cout << "-1 -1\n";
    else if (n == 2 && p == 2) cout << "-1 -1\n";
    else {
      for (int i = 2; i <= n; i++) {
        if (i != p) return cout << i << " " << 1 << "\n", 0;
      }
    }
  }
  else {
    if (n >= 2 * p) cout << "-1 -1\n";
    else if (n >= p) {
      ll k = 1;
      for (int i = 1; i <= n; i++) {
        if (i % p == 0) continue;
        k = (k * i) % p;
      }
      for (int j = 1; j < p; j++) {
        if ((k * j) % p == r) return cout << p << ' ' << j << '\n', 0;
      }
      cout << "-1 -1\n";
    }
    else {
      ll k = 1;
      for (int i = 1; i <= n; i++) k = (k * i) % p;
      ll marg = lpow(k, p - 2, p) * r % p;
      for (int i = 2; i <= n; i++) {
        ll mres = (marg * i) % p;
        if (mres && mres < i) return cout << i << ' ' << mres << '\n', 0;
      }
      cout << "-1 -1\n";
    }
  }
}
