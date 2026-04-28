#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, m;
  cin >> n >> m;

  ll last = 0, L = m, R = m, able = 1;
  for (int i = 0; i < n; i++) {
    ll t, nl, nr;
    cin >> t >> nl >> nr;
    if (!able) continue;

    L -= t - last;
    R += t - last;
    if (L > nr || R < nl) able = 0;

    L = max(L, nl);
    R = min(R, nr);
    last = t;
  }

  if (able) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
