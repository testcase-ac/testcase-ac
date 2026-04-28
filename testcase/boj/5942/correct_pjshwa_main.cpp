#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
vector<pair<int, ld>> adj[MAX + 1];
ld cdist[MAX + 1];

void solve() {
  int N, M, A, B; ld V; cin >> N >> M >> V >> A >> B;
  while (M--) {
    int u, v; ld p; cin >> u >> v >> p;
    adj[u].emplace_back(v, p);
  }

  fill(cdist, cdist + N + 1, 1e18);
  cdist[A] = V;

  // Bellman-ford
  for (int it = 1; it <= N; ++it) {
    for (int v = 1; v <= N; ++v) {
      for (auto& [u, p] : adj[v]) {
        if (cdist[u] > cdist[v] * p) {
          cdist[u] = cdist[v] * p;
          if (it == N) return cout << "0\n", void();
        }
      }
    }
  }

  cout << fixed << setprecision(7) << cdist[B] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
