#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e6, INF = 0x3f3f3f3f;
int parent[MAXN + 1], usz[MAXN + 1];
set<int> adj[MAXN + 1];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int N, M; cin >> N >> M;
  vector<int> A(2 * N), cdist(2 * N, INF);
  while (M--) {
    int x; cin >> x;
    A[x] = 1;
  }

  iota(parent, parent + 2 * N, 0);
  fill(usz, usz + 2 * N, 1);
  for (int u = 1; u <= 2 * N - 1; ++u) {
    for (int v : {u - 1, u + 1, u - N, u + N}) {
      if (v < 1 || v > 2 * N - 1) continue;
      if (A[v] == 1 && A[u] == 1) Union(u, v);
    }
  }

  deque<int> Q;
  vector<int> vis(2 * N);
  cdist[N] = 0; Q.push_back(N);
  while (!Q.empty()) {
    auto u = Q.front(); Q.pop_front();
    int ug = Find(u);

    for (int v : {u - 1, u + 1, u - N, u + N}) {
      if (v < 1 || v > 2 * N - 1) continue;

      int vg = Find(v);
      if (ug == vg) {
        if (cdist[v] > cdist[u] && !vis[v]) {
          cdist[v] = cdist[u];
          Q.push_front(v);
          vis[v] = 1;
        }

      }
      else {
        if (cdist[v] > cdist[u] + 1 && !vis[v]) {
          cdist[v] = cdist[u] + 1;
          Q.push_back(v);
          vis[v] = 1;
          adj[ug].insert(vg);
        }

      }
    }
  }

  ll ans = 0;
  queue<pll> Q2;
  Q2.push({N, 0});

  while (!Q2.empty()) {
    auto [ug, d] = Q2.front(); Q2.pop();
    for (int vg : adj[ug]) {
      if (A[vg]) {
        ans += d + usz[vg];
        Q2.push({vg, 0});
      }
      else {
        Q2.push({vg, d + 1});
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
