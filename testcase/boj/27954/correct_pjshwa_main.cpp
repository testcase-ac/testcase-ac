#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, Q; cin >> N >> M >> Q;

  vector<string> B(N);
  for (int i = 0; i < N; i++) cin >> B[i];

  vector<pii> qs;
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      qs.emplace_back(x - 1, y - 1);
    }
    else {
      int z = qs.size();
      for (int i = z - 1; i >= 0; i--) {
        auto& [xl, yl] = qs[i];
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
