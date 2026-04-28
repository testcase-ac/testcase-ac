#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[MAX + 1];
vector<pii> graph[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int n, m;
  cin >> n >> m;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    graph[u].push_back({v, c});
    graph[v].push_back({u, c});
  }
  for (int i = 1; i <= n; i++) {
    int cost;
    cin >> cost;
    pq.push({cost, i});
    parent[i] = i;
  }

  ll ans = 0;
  while (!pq.empty()) {
    auto [ai, ci] = pq.top();
    pq.pop();

    if (Find(0) == Find(ci)) continue;
    ans += ai;
    Union(0, ci);

    for (auto [v, c] : graph[ci]) pq.push({c, v});
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
