#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
int X[MAXN], Y[MAXN], R[MAXN], parent[MAXN];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i] >> R[i];

  vector<tuple<double, int, int>> edges;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    int dx = X[i] - X[j], dy = Y[i] - Y[j];
    edges.emplace_back(sqrt(dx * dx + dy * dy) - R[i] - R[j], i, j);
  }
  sort(edges.begin(), edges.end());

  iota(parent, parent + N, 0); double ans = 0;
  for (auto& [d, i, j] : edges) {
    if (Find(i) == Find(j)) continue;
    Union(i, j); ans += d;
  }
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
