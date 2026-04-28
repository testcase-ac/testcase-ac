#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300, MOD = 100030001;
int dp[MAXN + 1][MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;

  function<ll(int, int)> get = [&](int v, int h) {
    if (h == 0) return 0;
    return (dp[v][h] - dp[v][h - 1] + MOD) % MOD;
  };

  dp[1][1] = 1;
  for (int h = 2; h <= K; ++h) for (int v = 1; v <= N; ++v) {
    ll cur = 2 * get(v - 1, h - 1) % MOD;

    // Case where two children
    for (int lv = 1; lv < v - 1; ++lv) {
      ll rv = v - 1 - lv, add;

      // Left child has height h - 1
      add = get(lv, h - 1) * dp[rv][h - 1] % MOD;
      cur = (cur + add) % MOD;

      // Right child has height h - 1
      add = dp[lv][h - 1] * get(rv, h - 1) % MOD;
      cur = (cur + add) % MOD;

      // Subtract the case where both children have height h - 1
      add = get(lv, h - 1) * get(rv, h - 1) % MOD;
      cur = (cur - add + MOD) % MOD;
    }

    dp[v][h] = (dp[v][h - 1] + cur) % MOD;
  }

  cout << get(N, K) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
