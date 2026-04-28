#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;

int main() {
  fast_io();

  int n, x;
  cin >> n;
  map<ll, ll> m;
  for (int i = 0; i < n; i++) cin >> x, m[x]++;

  int i = 0;
  ll os = 0, ts = 0, ans = 0;
  for (auto iter = m.rbegin(); iter != m.rend(); ++iter) {
    auto [k, v] = *iter;
    i++;
    if (i <= 2) {
      ll at = (k * v) % MOD;
      at = (at * os) % MOD;
      ts = (ts + at) % MOD;
      os = (os + k * v) % MOD;
      continue;
    }
    ll aa = (k * v) % MOD;
    aa = (aa * ts) % MOD;
    ans = (ans + aa) % MOD;
    ll at = (k * v) % MOD;
    at = (at * os) % MOD;
    ts = (ts + at) % MOD;
    os = (os + k * v) % MOD;
  }

  cout << ans << '\n';
}
