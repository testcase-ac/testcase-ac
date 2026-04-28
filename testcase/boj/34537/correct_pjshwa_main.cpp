#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50000;
int parent[MAXN];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int N, M, B; cin >> N >> M >> B;

  using T = tuple<ll, ll, ll, ll, ll>;
  vector<T> E;
  for (int i = 0; i < M; ++i) {
    int u, v, w, x, y; cin >> u >> v >> w >> x >> y; --u, --v;
    E.emplace_back(u, v, w, x, y);
  }

  ll l = 1, r = 1e12;
  while (l < r) {
    ll m = (l + r) / 2;

    iota(parent, parent + N, 0);
    vector<T> edges;
    for (int i = 0; i < M; ++i) {
      auto& [u, v, w, x, y] = E[i];
      ll times = m <= w ? 0 : (m - w + x - 1) / x;
      ll cost = times * y;
      edges.emplace_back(cost, u, v, times, i);
    }
    sort(edges.begin(), edges.end());

    ll total = 0, ok = 1;
    for (auto& [cost, u, v, times, i] : edges) {
      if (Find(u) == Find(v)) continue;
      Union(u, v); total += cost;
      if (total > B) {
        ok = 0; break;
      }
    }
    if (ok) l = m + 1;
    else r = m;
  }

  ll X = l - 1;
  iota(parent, parent + N, 0);
  vector<T> edges;
  for (int i = 0; i < M; ++i) {
    auto& [u, v, w, x, y] = E[i];
    ll times = X <= w ? 0 : (X - w + x - 1) / x;
    ll cost = times * y;
    edges.emplace_back(cost, u, v, times, i);
  }
  sort(edges.begin(), edges.end());

  vector<ll> ans(M);
  for (auto& [cost, u, v, times, i] : edges) {
    if (Find(u) == Find(v)) continue;
    Union(u, v);
    ans[i] = times;
  }

  cout << X << '\n';
  for (int i = 0; i < M; ++i) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
