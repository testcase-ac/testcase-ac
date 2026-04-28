#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int n, l, h; cin >> n >> l >> h;
  vector<int> P(2 * n + 1);
  for (int i = 1; i <= n; i++) cin >> P[i];
  for (int i = 1; i <= 2 * n; i++) P[i] += P[i - 1];

  int pmin = INF, pmax = -INF;
  for (int s = l; s <= h; s++) {
    for (int p = 1; p <= s; p++) {
      int cnt = 0;
      for (int i = p;; i += s) {
        int val = P[i];
        if (i - s >= 0) val -= P[i - s];
        cnt += val > 0;
        if (i >= n) break;
      }
      pmin = min(pmin, cnt);
      pmax = max(pmax, cnt);
    }
  }
  cout << pmin << ' ' << pmax << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
