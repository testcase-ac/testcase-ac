#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
ll X[MAXN], Y[MAXN];
int parent[MAXN];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];

  iota(parent, parent + N, 0);
  while (M--) {
    int u, v; cin >> u >> v;
    Union(u - 1, v - 1);
  }

  using T = tuple<ll, int, int>;
  vector<T> edges;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    ll dx = X[i] - X[j], dy = Y[i] - Y[j];

    // vtx k should not lie on the line segment ij
    bool ok = true;
    for (int k = 0; k < N; ++k) {
      if (k == i || k == j) continue;
      if (X[k] < min(X[i], X[j]) || X[k] > max(X[i], X[j])) continue;
      if (Y[k] < min(Y[i], Y[j]) || Y[k] > max(Y[i], Y[j])) continue;

      ll dx1 = X[i] - X[k], dy1 = Y[i] - Y[k];
      ll dx2 = X[j] - X[k], dy2 = Y[j] - Y[k];
      if (dx * dy1 == dx1 * dy && dx * dy2 == dx2 * dy) {
        ok = false;
        break;
      }
    }
    if (ok) edges.emplace_back(dx * dx + dy * dy, i, j);
  }
  sort(edges.begin(), edges.end(), greater<T>());

  ll ans = 0;
  for (auto [w, u, v] : edges) {
    if (Find(u) == Find(v)) continue;
    Union(u, v); ans += w;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
