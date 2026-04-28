#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
int A[MAXN][MAXN], N;
vector<int> adj[MAXN];

bool is_bipartite() {
  queue<int> q; vector<int> color(N, -1);
  for (int i = 0; i < N; ++i) {
    if (color[i] != -1) continue;
    q.push(i); color[i] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        if (color[v] == -1) color[v] = 1 - color[u], q.push(v);
        else if (color[v] == color[u]) return false;
      }
    }
  }
  return true;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];

  int l = 0, r = 1e6 + 1;
  while (l < r) {
    int m = (l + r) / 2;

    for (int i = 0; i < N; ++i) adj[i].clear();
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
      if (A[i][j] < m) adj[i].push_back(j), adj[j].push_back(i);
    }

    if (is_bipartite()) l = m + 1;
    else r = m;
  }

  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
