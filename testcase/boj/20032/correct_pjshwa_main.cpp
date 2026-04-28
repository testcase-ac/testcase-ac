#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
vector<int> adj[MAX + 1];

void dfs(int v) {
  cout << v << ' ';
  for (int u : adj[v]) {
    dfs(u); cout << v << ' ';
  }
}

void solve() {
  int N; cin >> N;
  vector<pll> A(N);
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }

  auto [ox, oy] = A[0];
  vector<pll> pinf, ninf;
  map<pll, vector<pll>> by_slope;
  for (int i = 1; i < N; i++) {
    auto [cx, cy] = A[i];
    ll dist_sq = (cx - ox) * (cx - ox) + (cy - oy) * (cy - oy);
    if (cx == ox) {
      if (cy > oy) pinf.push_back({dist_sq, i + 1});
      else ninf.push_back({dist_sq, i + 1});
    }
    else {
      ll sy = cy - oy, sx = cx - ox;
      ll g = __gcd(sy, sx); g = abs(g);
      sy /= g; sx /= g;
      by_slope[{sy, sx}].push_back({dist_sq, i + 1});
    }
  }

  sort(pinf.begin(), pinf.end());
  sort(ninf.begin(), ninf.end());

  int li;
  li = 1; for (auto& [_, i] : pinf) adj[li].push_back(i), li = i;
  li = 1; for (auto& [_, i] : ninf) adj[li].push_back(i), li = i;
  for (auto& [_, v] : by_slope) {
    sort(v.begin(), v.end());
    li = 1; for (auto& [_, i] : v) adj[li].push_back(i), li = i;
  }

  cout << 2 * N - 1 << '\n';
  dfs(1);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
