#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
vector<int> graph[MAX + 1];
int sz[MAX + 1], level[MAX + 1], parent[MAX + 1], dc[MAX + 1];
vector<int> linv[MAX + 1];
bool vis[MAX + 1], erased[MAX + 1];

void dfs(int v, int l) {
  vis[v] = true;
  level[v] = l;
  sz[v] = 1;
  for (int d : graph[v]) {
    if (vis[d]) continue;
    parent[d] = v;
    dfs(d, l + 1);
    sz[v] += sz[d];
  }
  linv[l].push_back(v);
}

void erase(int v) {
  erased[v] = true;
  for (int d : graph[v]) {
    if (d == parent[v] || erased[d]) continue;
    erase(d);
  }
}

int cnt = 0;
void count(int v) {
  vis[v] = true;
  cnt++;
  for (int d : graph[v]) {
    if (vis[d] || erased[d]) continue;
    count(d);
  }
}

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  dfs(1, 1);

  for (int l = MAX; l >= 1; l--) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int v : linv[l]) pq.push({sz[v] - dc[v], v});
    while (pq.size() > k) {
      auto [ac, v] = pq.top();
      pq.pop();
      if (erased[v]) continue;
      dc[v] += ac;
      erase(v);
    }
    for (int v : linv[l]) dc[parent[v]] += dc[v];
  }

  memset(vis, 0, sizeof(vis));
  count(1);
  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
