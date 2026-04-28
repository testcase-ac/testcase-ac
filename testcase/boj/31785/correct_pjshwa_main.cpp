#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q; cin >> Q;

  deque<int> dq; int sum = 0;
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int x; cin >> x;
      dq.push_back(x); sum += x;
    }
    else {
      int Z = dq.size(), fh = 0;
      for (int i = 0; i < Z / 2; ++i) fh += dq[i];
      int bh = sum - fh;

      int it, acc = 0;
      if (fh <= bh) {
        it = Z / 2;
        while (it--) acc += dq.front(), dq.pop_front();
      }
      else {
        it = Z - Z / 2;
        while (it--) acc += dq.back(), dq.pop_back();
      }

      cout << acc << '\n';
      sum -= acc;
    }
  }

  for (int e : dq) cout << e << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
