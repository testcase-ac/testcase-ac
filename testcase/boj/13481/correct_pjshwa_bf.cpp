#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N;
  vector<pair<ll, ll>> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }

  ll area = 0;
  for (int i = 0; i < N; ++i) {
    auto [x1, y1] = A[i]; auto [x2, y2] = A[(i + 1) % N];
    area += x1 * y2 - x2 * y1;
  }
  if (area & 1) return cout << "0\n", void();

  int ans = N * (N - 3) / 2;
  for (int s = 0; s < N; ++s) for (int e = s + 2; e < N; ++e) {
    if (s == 0 && e == N - 1) continue;

    cout << "s: " << s << ", e: " << e << '\n';
    ll acc = 0;
    for (int i = s; i < e; ++i) {
      auto [x1, y1] = A[i]; auto [x2, y2] = A[i + 1];
      acc += (y1 + y2) * (x1 - x2);
    }
    auto [x1, y1] = A[e]; auto [x2, y2] = A[s];
    acc += (y1 + y2) * (x1 - x2);

    cout << "acc: " << acc << '\n';

    if (acc & 1) --ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
