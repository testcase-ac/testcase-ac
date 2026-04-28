#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

int N;
void solve() {
  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int w; cin >> w;
    if (i < j) edges.emplace_back(w, i, j);
  }
  sort(edges.begin(), edges.end());

  vector<int> parent(N);
  iota(parent.begin(), parent.end(), 0);
  function<int(int)> Find = [&](int x) {
    return parent[x] == x ? x : parent[x] = Find(parent[x]);
  };
  function<void(int, int)> Union = [&](int x, int y) {
    x = Find(x), y = Find(y);
    if (x != y) parent[y] = x;
  };

  vector<pii> adj[N];
  for (auto& [w, i, j] : edges) {
    if (Find(i) == Find(j)) continue;
    Union(i, j);
    cout << i + 1 << ' ' << j + 1 << ' ' << w << '\n';
    adj[i].push_back({j, w}); adj[j].push_back({i, w});
  }

  vector<vector<int>> D(N, vector<int>(N, INF));
  for (int i = 0; i < N; ++i) {
    queue<int> q; q.push(i); D[i][i] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto& [v, w] : adj[u]) {
        if (D[i][v] > D[i][u] + w) {
          D[i][v] = D[i][u] + w;
          q.push(v);
        }
      }
    }
  }

  for (auto& [w, i, j] : edges) {
    if (D[i][j] != w) {
      cout << i + 1 << ' ' << j + 1 << ' ' << w << '\n';
      return;
    }
  }

  auto& [w, i, j] = edges.back();
  cout << i + 1 << ' ' << j + 1 << ' ' << w << '\n';
}

int main() {
  fast_io();

  while (cin >> N) solve(), cout << '\n';
}
