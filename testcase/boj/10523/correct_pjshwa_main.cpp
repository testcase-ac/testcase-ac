#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; double p; cin >> n >> p;
  if (n == 1) return cout << "possible\n", void();

  vector<pll> P(n);
  for (auto& [x, y] : P) cin >> x >> y;

  mt19937 rng(0x14004);
  auto randint = [&rng](int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
  };

  int it = 300;
  while (it--) {
    int i = randint(0, n - 1), j;
    while ((j = randint(0, n - 1)) == i);

    auto [xi, yi] = P[i];
    auto [xj, yj] = P[j];

    // Count of points on line ij
    int cnt = 0;
    for (auto [x, y] : P) {
      if ((x - xi) * (yj - yi) == (y - yi) * (xj - xi)) cnt++;
    }

    if (100 * cnt >= n * p) return cout << "possible\n", void();
  }

  cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
