#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m, inv = 0; cin >> n >> m;
  if (n % 2 == 0) swap(n, m), inv = 1;

  vector<pii> traj;
  auto print = [&] () {
    int N = traj.size(), ok = 1;
    for (int i = 0; i < N; ++i) {
      auto [cx, cy] = traj[i];
      auto [nx, ny] = traj[(i + 1) % N];
      ok &= (abs(cx - nx) + abs(cy - ny) == 1);
      assert(ok);
    }

    cout << N << '\n';
    for (auto& [n, m] : traj) {
      if (inv) cout << m << ' ' << n << '\n';
      else cout << n << ' ' << m << '\n';
    }
  };

  for (int i = 1; i <= n; ++i) traj.emplace_back(i, 1);
  if (m == 2) {
    for (int i = n; i >= 1; --i) traj.emplace_back(i, 2);
    return print();
  }

  int f = 0;
  for (int j = 2; j <= m - 2; ++j) {
    if (f) for (int i = 2; i <= n; ++i) traj.emplace_back(i, j);
    else for (int i = n; i >= 2; --i) traj.emplace_back(i, j);
    f ^= 1;
  }

  if (m & 1) {
    for (int i = n; i >= 2; --i) {
      if (f) traj.emplace_back(i, m), traj.emplace_back(i, m - 1);
      else traj.emplace_back(i, m - 1), traj.emplace_back(i, m);
      f ^= 1;
    }
    for (int j = m - 1; j >= 2; --j) traj.emplace_back(1, j);
  } else {
    for (int j = m - 1; j <= m; ++j) {
      if (f) for (int i = 2; i <= n; ++i) traj.emplace_back(i, j);
      else for (int i = n; i >= 2; --i) traj.emplace_back(i, j);
      f ^= 1;
    }
    for (int j = m; j >= 2; --j) traj.emplace_back(1, j);
  }
  print();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
