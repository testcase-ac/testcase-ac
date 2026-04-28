#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, C, D, E, F; cin >> A >> B >> C >> D >> E >> F;

  int ans = 2 * E;
  while (1) {
    int open = A + 2 * B, close = C + 2 * D;
    if (open == close) break;

    if (open > close) {
      if (A == 0) --B;
      else if (B == 0) --A;
      else if (open - close >= 2) --B;
      else --A;
    } else {
      if (C == 0) --D;
      else if (D == 0) --C;
      else if (close - open >= 2) --D;
      else --C;
    }
  }

  if (A > 0 || B > 0) ans += 2 * F;
  ans += A + 2 * B + C + 2 * D;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
