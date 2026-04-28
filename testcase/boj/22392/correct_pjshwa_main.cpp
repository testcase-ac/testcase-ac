#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
vector<pii> graph[MAX + 1][2];
bool vis[MAX + 1][2];

void dfs(int i, int b) {
  vis[i][b] = 1;
  for (auto [u, w] : graph[i][b]) {
    if (!vis[u][w]) dfs(u, w);
  }
}

int N, M;
void solve() {
  for (int i = 1; i <= N; i++) {
    graph[i][0].clear();
    graph[i][1].clear();
    vis[i][0] = vis[i][1] = 0;
  }

  while (M--) {
    int u, v;
    cin >> u >> v;

    graph[u][0].push_back({v, 1});
    graph[u][1].push_back({v, 0});
    graph[v][0].push_back({u, 1});
    graph[v][1].push_back({u, 0});
  }

  dfs(1, 0);
  if (vis[1][1]) cout << "0\n";
  else {
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
      if (vis[i][0]) cnt++;
    }

    set<int> ans;
    for (int c : {cnt, N - cnt}) {
      if (c & 1) continue;
      ans.insert(c / 2);
    }

    cout << ans.size() << '\n';
    for (int e : ans) cout << e << '\n';
  }
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
