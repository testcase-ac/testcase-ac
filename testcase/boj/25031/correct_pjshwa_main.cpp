#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4, MOD = 1e9 + 7;
ll a[MAX + 1], p[MAX + 1], d[MAX + 1], n, x;

ll r(int i) {
  if (i > n) return 1;
  if (d[i] != -1) return d[i];

  ll res = 0;
  for (int j = i; j <= n; j++) {
    if (p[j] - p[i - 1] == x) res = (res + r(j + 1)) % MOD;
  }

  return d[i] = res;
}

void solve() {
  cin >> n;

  set<ll> candidates;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[i] = p[i - 1] + a[i];
    candidates.insert(p[i]);
  }

  ll ans = MOD - 1;
  for (auto candidate : candidates) {
    x = candidate;

    memset(d, -1, sizeof d);
    ans = (ans + r(1)) % MOD;
  }

  cout << ans << '\n';  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
