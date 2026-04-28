#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 1e8, MOD = 1e9 + 7;

void solve() {
  int p, q, r; cin >> p >> q >> r;

  // if a = 1, b = c
  // if b = c = 1, a
  int ans = min(q, r) + p - 1;
  // for (int a = 2; a <= min(p, 10'000); ++a) {
  //   for (int b = 2; b <= min(30, q); ++b) for (int c = 2; c <= r; ++c) {
  //     ll pw = 1, ok = 1;
  //     for (int i = 0; i < c; ++i) {
  //       pw *= b;
  //       if (pw > 30) {
  //         ok = 0;
  //         break;
  //       }
  //     }
  //     if (!ok) break;
  //     assert(pw <= 30);

  //     ll u = 1; ok = 1;
  //     for (int i = 0; i < pw; ++i) {
  //       u *= a;
  //       if (u > MAXL) {
  //         ok = 0;
  //         break;
  //       }
  //     }
  //     if (!ok) break;
  //     assert(u <= MAXL);

  //     if (u == (a ^ b ^ c)) {
  //       ans = (ans + 1) % MOD;
  //     }
  //   }
  // }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
