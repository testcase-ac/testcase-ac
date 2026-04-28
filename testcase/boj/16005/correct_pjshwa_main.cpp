#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 60, MOD = 1234567;
int b[MAX];
int C[MAX + 1][MAX + 1];

void solve() {
  ll n, k;
  cin >> n >> k;
  n--;

  for (int i = MAX - 1; i >= 0; i--) {
    if (n >= (1LL << i)) {
      b[i] = 1;
      n -= (1LL << i);
    }
  }

  ll ans = 0, uk = 0, pre = 0;
  for (int i = MAX - 1; i >= 0; i--) {
    if (b[i] == 0) continue;

    ll bsx = ((1LL << i) - 1) % MOD;
    if (i > 0 && k > uk) ans = (ans + bsx * C[i - 1][k - uk - 1]) % MOD;
    if (k >= uk) ans = (ans + pre * C[i][k - uk]) % MOD;

    uk++;
    pre = (pre + (1LL << i)) % MOD;
  }
  if (k == uk) ans = (ans + pre) % MOD;

  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i <= MAX; i++) C[i][0] = 1;
  for (int i = 1; i <= MAX; i++) for (int j = 1; j <= MAX; j++) {
    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
