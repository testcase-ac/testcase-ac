#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

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

const int MAX = 1e6;
int a[MAX + 1], s[MAX + 1];

void solve() {
  int n, p;
  cin >> n >> p;
  for (int i = n; i >= 0; i--) cin >> a[i];
  for (int i = 0; i <= n; i++) s[i % (p - 1)] = (s[i % (p - 1)] + a[i]) % p;

  cout << a[0] % p << '\n';
  for (int i = 1; i < p; i++) {
    ll cur = 0;
    for (int j = 0; j < p; j++) cur = (cur + s[j] * lpow(i, j, p)) % p;
    cout << cur << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
