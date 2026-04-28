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
  sort(A.begin(), A.end(), [](const pii& a, const pii& b) {
    auto [ar, as] = a; auto [br, bs] = b;

    int asum = ar * (ar - 1) * as + (ar + br) * (ar + br - 1) * bs;
    int bsum = br * (br - 1) * bs + (ar + br) * (ar + br - 1) * as;
    return asum < bsum;
  });

  int ans = 0, acc = 0;
  for (auto [r, s] : A) {
    for (int i = 1; i <= r; ++i) {
      ans += s * i;
      ans += s * i * acc / 10;
      ++acc;
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
