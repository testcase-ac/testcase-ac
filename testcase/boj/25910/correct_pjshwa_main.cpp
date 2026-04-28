#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MAXB = 20, INF = 0x3f3f3f3f;
vector<pii> graph[MAX + 1];
int group[MAX + 1][MAXB], usz[MAXB][2], g;
bool vis[MAX + 1][2];

void solve() {
  int N, X;
  cin >> N >> X;

  for (int i = 0; i < N - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;

    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  for (g = 0; g < 2; g++) {
    queue<tii> q;
    q.push({1, g, 0});
    vis[1][g] = true;

    while (!q.empty()) {
      auto [v, p, x] = q.front(); q.pop();

      for (int b = 0; b < MAXB; b++) {
        int m = (x & (1 << b)) ? 1 : 0;
        if (m ^ g) continue;
        group[v][b] = g;
        usz[b][g]++;
      }

      for (auto [u, c] : graph[v]) {
        if (vis[u][g]) continue;
        vis[u][g] = true;
        q.push({u, g, x ^ c});
      }
    }
  }

  int ans = INF;
  for (int i = 1; i <= N; i++) {
    int cur = 0;
    for (int b = 0; b < 20; b++) {
      int g = group[i][b], sz = usz[b][g];
      if (X & (1 << b)) cur += sz;
      else cur += N - sz;
    }
    ans = min(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
