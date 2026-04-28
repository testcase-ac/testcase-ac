#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, D; cin >> N >> D;

  vector<tii> A;
  for (int i = 0; i < N; i++) {
    int x, y, z; cin >> x >> y >> z;
    if (y <= D && y - x > z) A.push_back({x, y, z});
  }
  N = A.size();
  sort(A.begin(), A.end());

  int ans = D;
  for (int state = 0; state < (1 << N); state++) {
    vector<tii> E;
    for (int i = 0; i < N; i++) {
      if (state & (1 << i)) E.push_back(A[i]);
    }

    int z = E.size(), f = 1;
    for (int i = 1; i < z; i++) {
      auto [ps, pe, pd] = E[i - 1];
      auto [qs, qe, qd] = E[i];

      if (pe > qs) f = 0;
    }
    if (f == 0) continue;

    int cur = D;
    for (auto& [s, e, d] : E) {
      cur -= (e - s - d);
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
