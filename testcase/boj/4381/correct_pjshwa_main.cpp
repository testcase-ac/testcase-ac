#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int a[MAX];
vector<pii> traj;

int cross(int r) {
  if (r == 0) {
    traj.emplace_back(a[0], -1);
    return a[0];
  }
  if (r == 1) {
    traj.emplace_back(a[0], a[1]);
    return a[1];
  }
  if (r == 2) {
    traj.emplace_back(a[0], a[2]);
    traj.emplace_back(a[0], -1);
    traj.emplace_back(a[0], a[1]);
    return a[0] + a[1] + a[2];
  }

  if (a[0] + a[r - 1] > 2 * a[1]) {
    traj.emplace_back(a[0], a[1]);
    traj.emplace_back(a[0], -1);
    traj.emplace_back(a[r - 1], a[r]);
    traj.emplace_back(a[1], -1);
    return a[0] + 2 * a[1] + a[r] + cross(r - 2);
  }
  else {
    traj.emplace_back(a[0], a[r - 1]);
    traj.emplace_back(a[0], -1);
    traj.emplace_back(a[0], a[r]);
    traj.emplace_back(a[0], -1);
    return 2 * a[0] + a[r - 1] + a[r] + cross(r - 2);
  }
}

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a, a + n);

  cout << cross(n - 1) << '\n';
  for (auto [x, y] : traj) {
    if (y == -1) cout << x << '\n';
    else cout << x << ' ' << y << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
