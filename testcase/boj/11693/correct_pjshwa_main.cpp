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

  int n, m;
  cin >> n >> m;

  map<int, int> fcts;
  while (n % 2 == 0) {
    fcts[2]++;
    n /= 2;
  }
  for (int i = 3; i * i <= n; i += 2) {
    while (n % i == 0) {
      fcts[i]++;
      n /= i;
    }
  }
  if (n > 1) fcts[n]++;

  ll dst = 1;
  for (auto [k, v] : fcts) {
    ll pow = lpow(k, (ll)v * m + 1, MOD);
    dst = dst * (pow - 1) % MOD;
    dst = dst * lpow(k - 1, MOD - 2, MOD) % MOD;
  }

  cout << dst << '\n';
}
