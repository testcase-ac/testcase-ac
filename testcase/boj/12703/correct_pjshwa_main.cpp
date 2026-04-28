#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, INF = 0x3f3f3f3f;
int tc, N, G[MAXN], C[MAXN], V[MAXN], dp[MAXN][2];

bool is_leaf(int i) {
  return i >= (N - 1) / 2;
}

// i = index, t = target value
int rec(int i, int t) {
  if (dp[i][t] != -1) return dp[i][t];
  if (is_leaf(i)) return dp[i][t] = (V[i] == t ? 0 : INF);

  int l = 2 * i + 1, r = 2 * i + 2, ret = INF;

  // Simulate AND gate
  for (int lb = 0; lb < 2; ++lb) for (int rb = 0; rb < 2; ++rb) {
    if (G[i] == 0 && !C[i]) continue;
    if ((lb & rb) != t) continue;

    int cost = 1 - G[i];
    ret = min(ret, rec(l, lb) + rec(r, rb) + cost);
  }

  // Simulate OR gate
  for (int lb = 0; lb < 2; ++lb) for (int rb = 0; rb < 2; ++rb) {
    if (G[i] == 1 && !C[i]) continue;
    if ((lb | rb) != t) continue;

    int cost = G[i];
    ret = min(ret, rec(l, lb) + rec(r, rb) + cost);
  }
  return dp[i][t] = ret;
}

void solve() {
  cout << "Case #" << ++tc << ": ";

  int T; cin >> N >> T;
  for (int i = 0; i < (N - 1) / 2; ++i) cin >> G[i] >> C[i];
  for (int i = (N - 1) / 2; i < N; ++i) cin >> V[i];

  memset(dp, -1, sizeof(dp));
  int ans = rec(0, T);
  if (ans == INF) cout << "IMPOSSIBLE\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
