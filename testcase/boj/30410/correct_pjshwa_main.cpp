#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int f(int x) {
  int ret = 1;
  while (ret * 2 <= x) ret *= 2;
  return ret;
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  vector<pii> B;
  int streak1 = 0, streak2 = 0;
  for (int x : A) {
    if (x == 1) {
      ++streak1;
      if (streak2 > 0) {
        B.emplace_back(2, streak2);
        streak2 = 0;
      }
    }
    else {
      ++streak2;
      if (streak1 > 0) {
        if (streak1 % 2 == 0) B.emplace_back(2, streak1 / 2);
        else B.emplace_back(1, streak1);
        streak1 = 0;
      }
    }
  }
  if (streak1 > 0) {
    if (streak1 % 2 == 0) B.emplace_back(2, streak1 / 2);
    else B.emplace_back(1, streak1);
  }
  if (streak2 > 0) {
    B.emplace_back(2, streak2);
  }

  vector<pii> C;
  for (auto [p, v] : B) {
    if (!C.empty() && C.back().first == p) C.back().second += v;
    else C.emplace_back(p, v);
  }

  int Z = C.size(), ans = 0;
  for (int i = 0; i < Z; ++i) {
    auto [p, v] = C[i];

    if (p == 1) ans = max(ans, f(v));
    else {
      int cur = v;
      if (i > 0) cur += C[i - 1].second / 2;
      if (i < Z - 1) cur += C[i + 1].second / 2;
      ans = max(ans, 2 * f(cur));
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
