#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, Q; string S; cin >> N >> S >> Q;
  while (Q--) {
    int l, r; cin >> l >> r;
    string T = S.substr(l - 1, r - l + 1);

    int Z = T.size(), ans = 0;

    // i is the folding point
    for (int i = 1; i < Z; ++i) {
      int cur = 0;
      for (int l = 1;; ++l) {
        int li = i - l, ri = i + l - 1;
        if (li < 0 || ri >= Z) break;
        cur += (T[li] == T[ri]);
      }
      ans = max(ans, cur);
    }

    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
