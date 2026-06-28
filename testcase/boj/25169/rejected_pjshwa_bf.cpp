#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int r, s; cin >> r >> s;
    A.emplace_back(r, s);
  }

  int ans = 0x3f3f3f3f, p[N]; iota(p, p + N, 0);
  do {
    int cur = 0, acc = 0;
    for (int t = 0; t < N; ++t) {
      auto [r, s] = A[p[t]];
      for (int i = 1; i <= r; ++i) {
        cur += s * i;
        cur += s * i * acc / 10;
        ++acc;
      }
    }
    cout << "A = ";
    for (int t = 0; t < N; ++t) {
      cout << A[p[t]].first << ' ' << A[p[t]].second << ", ";
    }
    cout << "\ncur = " << cur << '\n';

    ans = min(ans, cur);
  } while (next_permutation(p, p + N));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
