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

  ll pre = 0, ans = 0; int C[2][4]{};
  for (int i = 0; i < N - 1; ++i) {
    auto [x1, y1] = A[i]; auto [x2, y2] = A[(i + 1) % N];

    ll npre = pre + (y1 + y2) * (x1 - x2);
    int p = 2 * (x2 & 1) + (y2 & 1), par = abs(npre) & 1;
    for (int e = 0; e < 4; ++e) {
      if (e == (p ^ 3)) ans += C[1 - par][e];
      else ans += C[par][e];
    }

    int w = 2 * (x1 & 1) + (y1 & 1);
    ++C[abs(pre) & 1][w];
    pre = npre;
  }

  cout << ans - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
