#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
vector<int> R[MAXN + 1], C[MAXN + 1];
int indegree_R[MAXN + 1], indegree_C[MAXN + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < M; ++i) {
    int x, y; cin >> x >> y;
    R[x].push_back(y); C[y].push_back(x);
    ++indegree_R[x]; ++indegree_C[y];
  }

  int ans = INF;
  queue<pair<int, int>> Q;
  {
    vector<int> indegree_R_copy(indegree_R, indegree_R + N + 1);
    vector<int> indegree_C_copy(indegree_C, indegree_C + N + 1);
    vector<int> vis_R(N + 1), vis_C(N + 1);
    set<pair<int, int>> vis;

    for (int r = 1; r <= N; ++r) {
      if (indegree_R_copy[r] <= K) vis_R[r] = 1, Q.push({r, 1});
    }
    for (int c = 1; c <= N; ++c) {
      if (indegree_C_copy[c] <= K) vis_C[c] = 1, Q.push({c, 2});
    }

    int cur = 0;
    while (!Q.empty()) {
      auto [u, t] = Q.front(); Q.pop();

      if (t % 2 == 1) {
        for (auto& j : R[u]) {
          if (vis.count({u, j})) continue;
          vis.insert({u, j}); cur = max(cur, t);
          --indegree_R_copy[u];
          if (!vis_C[j] && --indegree_C_copy[j] <= K) {
            vis_C[j] = 1;
            Q.push({j, t + 1});
          }
        }
      }
      else {
        for (auto& i : C[u]) {
          if (vis.count({i, u})) continue;
          vis.insert({i, u}); cur = max(cur, t);
          --indegree_C_copy[u];
          if (!vis_R[i] && --indegree_R_copy[i] <= K) {
            vis_R[i] = 1;
            Q.push({i, t + 1});
          }
        }
      }
    }

    if (vis.size() == M) ans = min(ans, cur);
  }

  {
    vector<int> indegree_R_copy(indegree_R, indegree_R + N + 1);
    vector<int> indegree_C_copy(indegree_C, indegree_C + N + 1);
    vector<int> vis_R(N + 1), vis_C(N + 1);
    set<pair<int, int>> vis;

    for (int c = 1; c <= N; ++c) {
      if (indegree_C_copy[c] <= K) vis_C[c] = 1, Q.push({c, 1});
    }
    for (int r = 1; r <= N; ++r) {
      if (indegree_R_copy[r] <= K) vis_R[r] = 1, Q.push({r, 2});
    }

    int cur = 0;
    while (!Q.empty()) {
      auto [u, t] = Q.front(); Q.pop();

      if (t % 2 == 1) {
        for (auto& i : C[u]) {
          if (vis.count({i, u})) continue;
          vis.insert({i, u}); cur = max(cur, t);
          --indegree_C_copy[u];
          if (!vis_R[i] && --indegree_R_copy[i] <= K) {
            vis_R[i] = 1;
            Q.push({i, t + 1});
          }
        }
      }
      else {
        for (auto& j : R[u]) {
          if (vis.count({u, j})) continue;
          vis.insert({u, j}); cur = max(cur, t);
          --indegree_R_copy[u];
          if (!vis_C[j] && --indegree_C_copy[j] <= K) {
            vis_C[j] = 1;
            Q.push({j, t + 1});
          }
        }
      }
    }

    if (vis.size() == M) ans = min(ans, cur);
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
