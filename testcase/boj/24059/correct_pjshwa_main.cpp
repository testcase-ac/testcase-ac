#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

  int n, m, a[3];
  cin >> n;
  for (int i = 0; i <= n; i++) cin >> a[i];
  cin >> m;

  if (n == 0) cout << a[0] % m << '\n';
  if (n == 1) cout << lpow(a[1], a[0], m) << '\n';
  if (n == 2) cout << lpow(a[2], lpow(a[1], a[0], m - 1) + m - 1, m) << '\n';
}
