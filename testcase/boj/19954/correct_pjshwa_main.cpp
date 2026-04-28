#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, M, X; cin >> N >> M >> X;

  map<int, int> maxp_m, lastp_m;
  while (X--) {
    int r, dir; ll c, move; cin >> r >> c >> dir; --r;
    move = r % (2 * M);
    c += dir * move;
    for (int t = 0; t < 2; ++t) {
      if (c < 1) {
        c -= 1;
        c = -c;
      } else if (c > M) {
        c -= (2 * M + 1);
        c = -c;
      }
    }
    assert(1 <= c && c <= M);

    ++maxp_m[c];
    lastp_m[c] = max(lastp_m[c], r);
  }

  int maxp = 0, lastp = 0x3f3f3f3f;
  for (auto& [_, v] : maxp_m) maxp = max(maxp, v);
  for (auto& [c, v] : maxp_m) {
    if (v == maxp) lastp = min(lastp, lastp_m[c]);
  }
  cout << maxp << ' ' << lastp << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
