#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MAXT = 1000;
vector<int> adj[MAXN + 1];
int dp[MAXT + 1][MAXN + 1];

void solve() {
  int N, T; cin >> N >> T;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  for (int i = 1; i <= T; ++i) {
    int x; cin >> x;
    for (int p = 1; p <= N; ++p) {
      dp[i][p] = max(dp[i][p], dp[i - 1][p] + (x == p));
      for (int q : adj[p]) {
        dp[i][q] = max(dp[i][q], dp[i - 1][p] + (x == q));
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= N; ++i) ans = max(ans, dp[T][i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
