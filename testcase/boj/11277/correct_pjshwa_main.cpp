#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> clauses;
  while (M--) {
    int i, j; cin >> i >> j;
    clauses.emplace_back(i, j);
  }

  for (int state = 0; state < (1 << N); state++) {
    bool f = true;
    for (auto [x, y] : clauses) {
      bool x1 = state & (1 << (abs(x) - 1));
      bool y1 = state & (1 << (abs(y) - 1));
      if (x < 0) x1 = !x1;
      if (y < 0) y1 = !y1;
      f &= (x1 | y1);
    }
    if (f) return cout << "1\n", void();
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
