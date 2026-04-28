#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(int x, int y) {
  cout << "Q " << x << " " << y << endl;
  int dist_sq; cin >> dist_sq;
  return dist_sq;
}

vector<pii> c[4];
vector<pii> cur;

void dfs(int i) {
  if (i == 4) {
    auto [ax, ay] = cur[0];
    cout << "A " << ax << " " << ay << endl;
    exit(0);
  }

  auto [cx, cy] = cur.back();
  for (int j = 0; j < c[i].size(); ++j) {
    auto [nx, ny] = c[i][j];
    int dif = abs(nx - cx) + abs(ny - cy);
    if (dif == 1) {
      cur.emplace_back(nx, ny);
      dfs(i + 1);
      cur.pop_back();
    }
  }
}

void solve() {
  int it = 0;
  for (auto [qx, qy] : {pii(989, 799), pii(938, 271), pii(171, 988), pii(897, 761)}) {
    int ans = ask(qx, qy);
    for (int x = 0; x <= 100; ++x) for (int y = 0; y <= 100; ++y) {
      int dist_sq = (x - qx) * (x - qx) + (y - qy) * (y - qy);
      if (dist_sq == ans) c[it].emplace_back(x, y);
    }
    ++it;
  }

  for (auto [x, y] : c[0]) {
    cur.emplace_back(x, y);
    dfs(1);
    cur.pop_back();
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
