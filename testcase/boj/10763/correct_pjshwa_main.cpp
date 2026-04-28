#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
int q[MAX + 1];
vector<int> graph[MAX + 1];
int cdist[MAX + 1][MAX + 1];
int d[MAX + 1];
int n, e;

int r(int v) {
  if (d[v] != -1) return d[v];

  int res = 0;
  for (int j = 1; j <= n; j++) {
    if (q[v] <= q[j] || cdist[v][j] == INF) continue;
    res = max(res, r(j) - e * cdist[v][j]);
  }

  return d[v] = res + q[v];
}

void solve() {
  cin >> n >> e;
  for (int i = 1; i <= n; i++) {
    int d;
    cin >> q[i] >> d;
    while (d--) {
      int x;
      cin >> x;
      graph[i].push_back(x);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cdist[i][j] = INF;

    queue<pii> q;
    cdist[i][i] = 0;
    q.push({i, 0});
    while (!q.empty()) {
      auto& [v, d] = q.front();
      q.pop();

      for (int u : graph[v]) {
        if (cdist[i][u] > d + 1) {
          cdist[i][u] = d + 1;
          q.push({u, d + 1});
        }
      }
    }
  }

  memset(d, -1, sizeof d);
  int ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, r(i));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
