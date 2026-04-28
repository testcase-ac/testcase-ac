#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, INF = 0x3f3f3f3f;
int cdist[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;

  memset(cdist, 0x3f, sizeof(cdist));
  for (int i = 0; i < N; ++i) cdist[i][i] = 0;
  while (M--) {
    int u, v, w; cin >> u >> v >> w; --u, --v;
    w = min(w, cdist[u][v]);
    cdist[u][v] = cdist[v][u] = w;
  }
  for (int k = 0; k < N; ++k) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cdist[i][j] = min(cdist[i][j], cdist[i][k] + cdist[k][j]);
  }

  // cout << "cdist =\n";
  // for (int i = 0; i < N; ++i) {
  //   for (int j = 0; j < N; ++j) {
  //     if (cdist[i][j] == INF) cout << "INF ";
  //     else cout << cdist[i][j] << ' ';
  //   }
  //   cout << '\n';
  // }

  int K; cin >> K;
  vector<tuple<int, int, int>> R;
  while (K--) {
    int u, v, t; cin >> u >> v >> t; --u, --v;
    R.emplace_back(u, v, t);
  }

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    int ok = 1;
    for (auto& [u, v, t] : R) {
      // If this is already the shortest path
      // Teleport should not reduce the distance
      if (cdist[u][v] == t) {
        int c1 = cdist[u][i] + cdist[j][v] >= t;
        int c2 = cdist[u][j] + cdist[i][v] >= t;
        ok &= (c1 && c2);
      }

      // If this is not the shortest path
      // Teleport should make the distance exactly t
      else {
        int c1 = cdist[u][i] + cdist[j][v] == t;
        int c2 = cdist[u][j] + cdist[i][v] == t;
        ok &= (c1 || c2);
      }
    }

    if (ok) {
      cout << min(i, j) + 1 << ' ' << max(i, j) + 1 << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
