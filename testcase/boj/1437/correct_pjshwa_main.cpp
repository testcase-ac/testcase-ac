#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 10007;

void solve() {
  int V; cin >> V;
  if (V <= 4) return cout << V << '\n', void();

  ll ans = 1;
  if (V % 3 == 0) {
    for (int i = 0; i < V / 3; i++) {
      ans = (ans * 3) % MOD;
    }
  }
  else if (V % 3 == 1) {
    for (int i = 0; i < (V / 3) - 1; i++) {
      ans = (ans * 3) % MOD;
    }
    ans = (ans * 4) % MOD;
  }
  else {
    for (int i = 0; i < V / 3; i++) {
      ans = (ans * 3) % MOD;
    }
    ans = (ans * 2) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
