#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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

ll modm(ll val, ll m) {
  if (val < 0) return m - (-val % m);
  else return val % m;
}

int main() {
  fast_io();

  ll m, seed, x1, x2;
  cin >> m >> seed >> x1 >> x2;

  ll a = (lpow(modm(x1 - seed, m), m - 2, m) * modm(x2 - x1, m)) % m;
  ll c = modm(x1 - a * seed, m);
  cout << a << ' ' << c;
}
