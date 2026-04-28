#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q; cin >> Q;
  map<int, int> P;

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int x; cin >> x;
      ++P[x];
    }
    if (op == 2) {
      int x; cin >> x;
      if (P.count(x) && !--P[x]) P.erase(x);
    }
    if (op == 3) {
      if (P.empty()) {
        cout << "0\n";
        continue;
      }

      int p = P.begin()->first, ans = 1;
      while (1) {
        auto it = P.lower_bound(2 * p);
        if (it == P.end()) break;
        p = it->first; ++ans;
      }
      cout << ans << '\n';
    }
  }
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
