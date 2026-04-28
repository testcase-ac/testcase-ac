#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll m, n, z;
ll g[70], d[70][70][2];

// current digit, non-zero used, following original number
ll r(int i, int tot, bool f) {
  if (d[i][tot][f] != -1) return d[i][tot][f];
  if (i == z) return d[i][tot][f] = (tot == n);

  ll ret = 0;
  if (f) {
    int c = g[i];
    if (c == 0) {
      ret += r(i + 1, tot, 1);
    }
    else {
      ret += r(i + 1, tot, 0);
      ret += r(i + 1, tot + 1, 0) * (c - 1);
      ret += r(i + 1, tot + 1, 1);
    }
  }
  else {
    ret += r(i + 1, tot, 0);
    ret += r(i + 1, tot + 1, 0) * (m - 1);
  }

  return d[i][tot][f] = ret;
}

ll upto(ll x) {
  if (x == 0) return 0;

  z = 0;
  memset(g, 0, sizeof(g));

  while (x) {
    g[z++] = x % m;
    x /= m;
  }
  reverse(g, g + z);

  memset(d, -1, sizeof(d));
  return r(0, 0, 1);
}

void solve() {
  ll a, b;
  cin >> a >> b >> m >> n;
  cout << upto(b) - upto(a - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
