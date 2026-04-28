#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 11;
ll d[1 << MAX], ans[MAX + 1], p;

ll r(ll u) {
  if (d[u] != -1) return d[u];
  if (u == 0) return 1;

  ll ret = 0;
  for (int s = 1; s < (1 << p); s++) {
    if (s != (u & s)) continue;
    ret += r(u ^ s);
  }

  return d[u] = ret;
}

void solve() {
  int n;
  cin >> n;
  cout << ans[n] << '\n';
}

int main() {
  fast_io();

  for (p = 1; p <= MAX; p++) {
    memset(d, -1, sizeof(d));
    for (int s = 1; s < (1 << p); s++) ans[p] += r(s);
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
