#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q; cin >> Q;
  map<int, int> maxy;

  while (Q--) {
    int op, x; cin >> op >> x;
    if (op == 1) {
      int cury = 0;
      for (int i = x; i < x + 4; ++i) cury = max(cury, maxy[i]);
      for (int i = x; i < x + 4; ++i) maxy[i] = cury + 1;
    }
    if (op == 2) {
      maxy[x] += 4;
    }
    if (op == 3) {
      cout << (maxy.count(x) ? maxy[x] : 0) << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
