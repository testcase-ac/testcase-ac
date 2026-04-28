#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15, INF = 0x3f3f3f3f;
int cdist[MAXN][MAXN], deg[MAXN];
int dp[1 << MAXN], N;

int rec(int s) {
  if (s == 0) return 0;
  if (dp[s] != -1) return dp[s];

  int ret = INF;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    if (!(s & (1 << i)) || !(s & (1 << j))) continue;
    ret = min(ret, cdist[i][j] + rec(s ^ (1 << i) ^ (1 << j)));
  }
  return dp[s] = ret;
}

void solve() {
  int M, ans = 0; cin >> M;

  memset(cdist, 0x3f, sizeof(cdist));
  memset(deg, 0, sizeof(deg));
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    --u; --v; ans += w;
    cdist[u][v] = cdist[v][u] = min(cdist[u][v], w);
    ++deg[u]; ++deg[v];
  }

  // Floyd-Warshall
  for (int k = 0; k < N; ++k) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cdist[i][j] = min(cdist[i][j], cdist[i][k] + cdist[k][j]);
  }

  int s = 0;
  for (int i = 0; i < N; ++i) if (deg[i] & 1) s |= 1 << i;

  memset(dp, -1, sizeof(dp));
  int add = rec(s);
  cout << ans + add << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
