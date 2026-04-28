#include <bits/stdc++.h>
#include "../../debug.h"
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  int N;
  cin >> N;

  map<int, int> d;
  d[0] = 1;

  int ans = 0;
  for (int i = 0, x; i < N; i++) {
    cin >> x;
    ans = (ans + d[x]) % MOD;
    ans = (ans + d[-x]) % MOD;

    map<int, int> nd;
    nd[0] = 1;

    for (auto [k, v] : d) {
      nd[k + x] = (nd[k + x] + v) % MOD;
      nd[k - x] = (nd[k - x] + v) % MOD;
    }

    d = nd;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
