#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e7, MOD = 998244353;
const int R[25] = {
  -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29030400,
  145152000, 17819647, 160376823, 765900700, 533557047, 137739482,
  826436892, 622029018, 230824062, 773400038
};
ll ofac[MAX + 1], efac[MAX + 1];

void solve() {
  ll N; cin >> N;
  if (N <= 24) return cout << R[N] << '\n', void();

  ll ans = 773400038, S = 24;
  for (ll g = 8;; g += 2) {
    if (N >= S + 2 * g) {
      ans = (ans * ofac[g]) % MOD;
      ans = (ans * efac[g]) % MOD;
      S += 2 * g;
    }
    else if (N >= S + g) {
      ans = (ans * ofac[g]) % MOD;
      ans = (ans * efac[N - S - g]) % MOD;
      break;
    }
    else {
      ans = (ans * ofac[N - S]) % MOD;
      break;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  ofac[0] = efac[0] = 1;
  for (int i = 1; i <= MAX; i++) {
    ofac[i] = (ofac[i - 1] * (2 * i - 1)) % MOD;
    efac[i] = (efac[i - 1] * (2 * i)) % MOD;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
