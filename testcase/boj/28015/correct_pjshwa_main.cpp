#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    int c1 = 0, c2 = 0, cc = 0;
    for (int j = 0; j < M; j++) {
      int x; cin >> x;
      if (cc == x) continue;

      if (x == 1) c1++;
      else if (x == 2) c2++;
      else {
        ans += min(c1 + 1, c2 + 1);
        c1 = c2 = 0;
      }
      cc = x;
    }
    if (c1 || c2) ans += min(c1 + 1, c2 + 1);
  }
  cout << ans << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
