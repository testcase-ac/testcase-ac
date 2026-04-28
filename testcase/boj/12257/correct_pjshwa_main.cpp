#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<int> graph[MAX + 1];
int sz[MAX + 1], d[MAX + 1], cur;

void dfs1(int v, int p) {
  sz[v] = 1;
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs1(u, v);
    sz[v] += sz[u];
  }
}

// d[v]: how many nodes you will save, if you keep v
void dfs2(int v, int p) {
  priority_queue<int, vector<int>, greater<int>> pq;

  d[v] = 1;
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs2(u, v);
    pq.push(d[u]);
  }

  while (pq.size() > 2) pq.pop();
  if (pq.size() == 1) pq.pop();

  while (!pq.empty()) {
    d[v] += pq.top();
    pq.pop();
  }
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) graph[i].clear();

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int ans = INF;
  for (int i = 1; i <= N; i++) {
    memset(sz, 0, sizeof(sz));
    memset(d, 0, sizeof(d));

    dfs1(i, -1);
    dfs2(i, -1);
    ans = min(ans, N - d[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
