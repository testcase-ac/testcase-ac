#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
int cdist[MAXN][MAXN];

void solve() {
  int N, W, P; cin >> N >> W >> P;

  memset(cdist, 0x3f, sizeof(cdist));
  for (int j = 0; j < W; ++j) {
    int u, v, w; cin >> u >> v >> w; --u, --v;
    cdist[u][v] = cdist[v][u] = w;
  }

  for (int k = 0; k < N; ++k) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cdist[i][j] = min(cdist[i][j], cdist[i][k] + cdist[k][j]);
  }

  while (P--) {
    int u, v; cin >> u >> v; --u, --v;
    cout << cdist[u][v] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
