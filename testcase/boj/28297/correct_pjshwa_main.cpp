#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int parent[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int N; cin >> N;
  vector<tuple<int, int, int>> A(N);
  for (auto& [x, y, r] : A) cin >> x >> y >> r;

  vector<tuple<double, int, int>> E;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    auto [xi, yi, ri] = A[i]; auto [xj, yj, rj] = A[j];

    double W;
    int dist_o = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);
    if (dist_o <= (ri + rj) * (ri + rj)) W = 0;
    else {
      if (ri < rj) swap(ri, rj);

      double d = sqrt(dist_o - (ri - rj) * (ri - rj));
      double th = atan((ri - rj) / d);
      W = ri * (M_PI + 2 * th) + rj * (M_PI - 2 * th) + 2 * d;
    }
    E.emplace_back(W, i, j);
  }
  sort(E.begin(), E.end());

  iota(parent, parent + N, 0); double ans = 0;
  for (auto [w, u, v] : E) {
    if (Find(u) != Find(v)) {
      Union(u, v);
      ans += w;
    }
  }
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
