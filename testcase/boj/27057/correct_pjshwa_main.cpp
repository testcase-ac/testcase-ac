#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300, INF = 0x3f3f3f3f;
int cdist[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;

  memset(cdist, 0x3f, sizeof(cdist));
  for (int i = 0; i < N; ++i) cdist[i][i] = 0;
  while (M--) {
    int k; cin >> k;
    vector<int> V(k);
    for (auto &x : V) cin >> x, --x;
    for (int u : V) for (int v : V) {
      if (u != v) cdist[u][v] = 1;
    }
  }

  for (int k = 0; k < N; ++k) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cdist[i][j] = min(cdist[i][j], cdist[i][k] + cdist[k][j]);
  }

  int ans = INF;
  for (int i = 0; i < N; ++i) {
    int sum = 0;
    for (int j = 0; j < N; ++j) sum += cdist[i][j];
    ans = min(ans, sum * 100 / (N - 1));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
