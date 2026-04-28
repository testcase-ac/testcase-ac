#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int h[MAXN], dp[MAXN], D[MAXN];
vector<int> adj[MAXN];

int rec(int x) {
  if (dp[x] != -1) return dp[x];
  if (D[x]) return dp[x] = 0;

  dp[x] = 1;
  for (int y : adj[x]) dp[x] &= rec(y);
  return dp[x];
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> h[i];
  while (M--) {
    int u, v; cin >> u >> v; --u, --v;
    if (h[u] < h[v]) adj[v].push_back(u);
    else adj[u].push_back(v);
  }
  int K; cin >> K;
  for (int i = 0; i < K; ++i) {
    int x; cin >> x; --x;
    D[x] = 1;
  }

  memset(dp, -1, sizeof(dp)); int cnt = 0;
  for (int i = 0; i < N; ++i) cnt += rec(i);
  if (cnt == 0) cout << "no ";
  cout << "flood\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
