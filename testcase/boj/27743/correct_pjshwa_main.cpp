#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

__int128_t lpow(__int128_t x, __int128_t y, ll m) {
  __int128_t r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  ll nll, mll; cin >> nll >> mll;

  __int128_t N = nll, M = mll, ans;
  if (M == 1) ans = (lpow(2, N, MOD) - 1 + MOD) % MOD;
  else {
    ans = 4 * M % MOD;
    ans = (ans * (lpow(2, N - 1, MOD) - 1 + MOD)) % MOD;
    ans = (ans + M) % MOD;
    ans = (ans + M) % MOD;
    ans = (ans - 1 + MOD) % MOD;
  }

  cout << (ll)ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
