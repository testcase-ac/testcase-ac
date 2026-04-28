#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10, INF = 0x3f3f3f3f;
int S[MAX], mask;
vector<int> adj[MAX];
bool vis[MAX];

void dfs1(int v) {
  vis[v] = 1;
  for (int u : adj[v]) {
    if (vis[u] || !(mask & (1 << u))) continue;
    dfs1(u);
  }
}

void dfs2(int v) {
  vis[v] = 1;
  for (int u : adj[v]) {
    if (vis[u] || (mask & (1 << u))) continue;
    dfs2(u);
  }
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> S[i];
  for (int i = 0; i < N; i++) {
    int M; cin >> M;
    while (M--) {
      int x; cin >> x;
      adj[i].push_back(x - 1);
    }
  }

  int ans = INF;
  for (mask = 0; mask < (1 << N); mask++) {
    memset(vis, 0, sizeof(vis));

    int cc1 = 0, cc2 = 0;
    for (int i = 0; i < N; i++) {
      if (mask & (1 << i)) {
        if (!vis[i]) dfs1(i), cc1++;
      }
      else {
        if (!vis[i]) dfs2(i), cc2++;
      }
    }

    int cnt = accumulate(vis, vis + N, 0);
    if (cc1 == 1 && cc2 == 1 && cnt == N) {
      int sz1 = 0, sz2 = 0;
      for (int i = 0; i < N; i++) {
        if (mask & (1 << i)) sz1 += S[i];
        else sz2 += S[i];
      }
      ans = min(ans, abs(sz1 - sz2));
    }
  }

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
