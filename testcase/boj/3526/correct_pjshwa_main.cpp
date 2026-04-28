#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<pii> graph[MAX + 1];
int cdist[MAX + 1];
bool vis[MAX + 1];

int bfs(int s, int e) {
  memset(cdist, -1, sizeof(cdist));
  queue<pii> q;
  q.push({s, 0});
  cdist[s] = 0;

  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();

    for (auto &e : graph[u]) {
      int v = e.first;
      int w = e.second;
      if (cdist[v] == -1) {
        cdist[v] = d + 1;
        q.push({v, d + 1});
      }
    }
  }

  return cdist[e];
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int ai, bi, ci;
    cin >> ai >> bi >> ci;
    graph[ai].push_back({bi, ci});
    graph[bi].push_back({ai, ci});
  }

  int md = bfs(1, n);
  bfs(n, 1);

  queue<pii> q;
  q.push({1, 0});
  vis[1] = true;

  vector<int> traj;

  while (1) {
    queue<pii> nq;

    int mw = 1e9, qs = q.size();
    while (qs--) {
      auto [u, d] = q.front();
      q.pop();

      for (auto &e : graph[u]) {
        auto [v, w] = e;
        if (vis[v] || cdist[v] != md - d - 1) continue;
        mw = min(mw, w);
      }

      q.push({u, d});
    }
    traj.push_back(mw);

    while (!q.empty()) {
      auto [u, d] = q.front();
      q.pop();

      for (auto &e : graph[u]) {
        auto [v, w] = e;
        if (vis[v] || cdist[v] != md - d - 1) continue;
        if (w != mw) continue;

        vis[v] = true;
        nq.push({v, d + 1});
      }

    }

    if (nq.empty()) break;
    else q = nq;
  }
  traj.pop_back();

  cout << md << '\n';
  for (int e : traj) {
    cout << e << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
