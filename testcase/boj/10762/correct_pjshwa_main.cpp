#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, B; cin >> N >> B;

  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int si, pi; cin >> si >> pi;
    A.emplace_back(pi, si);
  }
  sort(A.begin(), A.end());

  vector<pii> L, R;
  for (int i = 0; i < N; ++i) {
    auto [pi, si] = A[i];
    if (pi > B) break;
    L.emplace_back(pi, si);
  }
  for (int i = N - 1; i >= 0; --i) {
    auto [pi, si] = A[i];
    if (pi < B) break;
    R.emplace_back(pi, si);
  }
  reverse(R.begin(), R.end());

  int ans = INF, lz = L.size(), rz = R.size();
  {
    int ri = 0;
    for (int li = lz - 1; li >= 0; --li) {
      auto [lp, ls] = L[li];
      while (ri < rz) {
        auto [rp, rs] = R[ri];
        int pow = rp - lp - 1;

        if (rs <= pow) ++ri;
        else break;
      }

      if (ri == rz) break;
      auto [rp, rs] = R[ri];
      ans = min(ans, max(0, rp - lp - ls));
    }
  }

  reverse(L.begin(), L.end());
  reverse(R.begin(), R.end());

  {
    int li = 0;
    for (int ri = rz - 1; ri >= 0; --ri) {
      auto [rp, rs] = R[ri];
      while (li < lz) {
        auto [lp, ls] = L[li];
        int pow = rp - lp - 1;

        if (ls <= pow) ++li;
        else break;
      }

      if (li == lz) break;
      auto [lp, ls] = L[li];
      ans = min(ans, max(0, rp - lp - rs));
    }

  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
