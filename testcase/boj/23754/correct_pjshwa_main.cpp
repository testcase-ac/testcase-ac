#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 400, INF = 1e9 + 7;
pii a[MAX + 1], b[MAX + 1];
vector<int> graph[MAX + 1];
int indegree[MAX + 1];
int d[MAX + 1][201][201];

int r(int i, int x, int y) {
  if (i == 0) {
    if (x == 0 && y == 0) return 0;
    else return INF;
  }
  if (d[i][x][y] != -1) return d[i][x][y];

  auto [xi, yi] = a[i];
  int ret = r(i - 1, x, y);
  ret = min(ret, r(i - 1, max(x - xi, 0), max(y - yi, 0)) + 1);
  return d[i][x][y] = ret;
}

void solve() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    indegree[b]++;
  }
  for (int i = 1; i <= n; i++) cin >> b[i].first >> b[i].second;

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }
  vector<int> order;

  priority_queue<int, vector<int>, greater<int>> nq;
  while (1) {
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      order.push_back(u);
      for (int v : graph[u]) {
        if (!--indegree[v]) nq.push(v);
      }
    }
    if (!nq.size()) break;
    while (!nq.empty()) q.push(nq.top()), nq.pop();
  }

  if (order.size() < n) return cout << "-1\n", void();
  for (int i = 1; i <= n; i++) a[i] = b[order[i - 1]];

  memset(d, -1, sizeof(d));
  int ans = r(n, x, y);
  if (ans == INF) cout << "-1\n";
  else {
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
      if (ans == r(i, x, y)) {
        cout << order[i - 1] << '\n';
        break;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
