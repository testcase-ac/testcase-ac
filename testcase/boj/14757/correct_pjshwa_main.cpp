#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN + 1];
int indegree[MAXN + 1];

int N, M;
void solve() {
  memset(indegree, 0, sizeof(indegree));
  for (int i = 1; i <= N; ++i) adj[i].clear();

  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); ++indegree[v];
  }

  queue<int> q;
  for (int i = 1; i <= N; ++i) if (indegree[i] == 0) q.push(i);

  int ans = 1;
  for (int i = 1; i <= N; ++i) {
    if (q.empty()) return cout << "0\n", void();
    if (q.size() > 1) ans = 2;

    int u = q.front(); q.pop();
    for (int v : adj[u]) if (--indegree[v] == 0) q.push(v);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
