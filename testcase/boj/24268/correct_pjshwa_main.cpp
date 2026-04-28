#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll INF = 1e18;

void solve() {
  int n, d;
  cin >> n >> d;

  int p[10];
  for (int i = 0; i < d; i++) p[i] = i;

  ll ans = INF;
  do {
    if (p[d - 1] == 0) continue;

    ll pw = 1, cur = 0;
    for (int i = 0; i < d; i++) {
      cur += p[i] * pw;
      pw *= d;
    }
    if (cur > n) ans = min(ans, cur);
  } while (next_permutation(p, p + d));

  if (ans == INF) cout << -1 << '\n';
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
