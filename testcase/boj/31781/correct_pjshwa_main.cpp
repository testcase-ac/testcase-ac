#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using T = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
vector<T> B[MAXN + 1];
vector<int> adj[MAXN + 1];
int indegree[MAXN + 1], o_indegree[MAXN + 1], vis[MAXN + 1];

void solve() {
  int N, H; cin >> N >> H;
  for (int i = 0; i < N; ++i) {
    int h, s, e; cin >> h >> s >> e;
    B[h].emplace_back(s, e, i);
  }
  for (int i = 1; i <= H; ++i) sort(B[i].begin(), B[i].end());

  deque<T> blocks_below;
  for (int h = 2; h <= H; ++h) {
    int j = 0, Z = B[h - 1].size();
    for (auto& [s, e, i] : B[h]) {
      while (j < Z) {
        auto& [bs, be, bi] = B[h - 1][j];
        if (bs < e) blocks_below.emplace_back(bs, be, bi), ++j;
        else break;
      }
      while (!blocks_below.empty() && get<1>(blocks_below.front()) <= s) {
        blocks_below.pop_front();
      }

      for (auto& [bs, be, bi] : blocks_below) {
        adj[bi].push_back(i);
        ++indegree[i];
      }
    }

    while (!blocks_below.empty()) blocks_below.pop_front();
  }

  copy(indegree, indegree + N, o_indegree);
  queue<int> Q; int ans = 0;
  for (int h = 1; h <= H; ++h) {
    for (auto& [s, e, i] : B[h]) {
      if (vis[i]) continue;

      int cur = 0; Q.push(i);
      vector<int> traj{i};
      while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        ++cur; vis[u] = 1;
        for (int v : adj[u]) {
          traj.push_back(v);
          if (--indegree[v] == 0) Q.push(v);
        }
      }
      ans = max(ans, cur);
      for (int u : traj) indegree[u] = o_indegree[u];
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
