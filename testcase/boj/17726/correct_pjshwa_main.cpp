#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXK = 10000, MAXN = 1000;
int parent[MAXK + 1][MAXN + 1];

int Find(int l, int x) {
  if (x == parent[l][x]) return x;
  else {
    int p = Find(l, parent[l][x]);
    parent[l][x] = p;
    return p;
  }
}

void Union(int l, int x, int y) {
  x = Find(l, x);
  y = Find(l, y);

  if (x != y) parent[l][y] = x;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 1; i <= K; i++) iota(parent[i], parent[i] + N + 1, 0);

  vector<tuple<int, int, int, int>> edges;
  for (int i = 0; i < M; i++) {
    int u, v, w; cin >> u >> v >> w;
    edges.push_back({w, u, v, i});
  }
  sort(edges.begin(), edges.end(), greater<>());

  vector<int> ans(M);
  for (auto [w, u, v, i] : edges) {
    int left = 1, right = K + 1;
    while (left < right) {
      int mid = (left + right) / 2;

      if (Find(mid, u) != Find(mid, v)) right = mid;
      else left = mid + 1;
    }
    if (left == K + 1) continue;

    Union(left, u, v);
    ans[i] = left;
  }

  for (int i = 0; i < M; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
