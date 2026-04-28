#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 9;
ll d1[MAX + 1], d2[MAX + 1];

void solve() {
  int n; cin >> n;

  ll ans = (d1[n] * d2[n]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  d1[0] = d2[0] = 1;
  for (int i = 1; i <= MAX; i++) {
    for (int j = 1; j <= 2; j++) {
      if (i - j < 0) break;
      d1[i] = (d1[i] + d1[i - j]) % MOD;
    }
  }
  for (int i = 1; i <= MAX; i++) {
    for (int j = 1; j <= 4; j++) {
      if (i - j < 0) break;
      d2[i] = (d2[i] + d2[i - j]) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
