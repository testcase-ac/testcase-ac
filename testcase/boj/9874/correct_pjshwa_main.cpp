#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 12;
int X[MAXN], Y[MAXN], nxt[MAXN], N;
vector<int> adj[2 * MAXN];
int vis[MAXN], ans;

void dfs(int t) {

  if (t == N / 2) {
    // check if cycle exists
    vector<int> indegree(2 * N, 0);
    for (int i = 0; i < 2 * N; ++i) for (int j : adj[i]) ++indegree[j];

    queue<int> q;
    for (int i = 0; i < 2 * N; ++i) if (indegree[i] == 0) q.push(i);

    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) if (--indegree[v] == 0) q.push(v);
    }

    int ok = 1;
    for (int i = 0; i < 2 * N; ++i) ok &= indegree[i] == 0;
    if (!ok) ++ans;
  }
  else {
    int i = 0;
    while (vis[i]) ++i;
    for (int j = i + 1; j < N; ++j) {
      if (vis[j]) continue;

      vis[i] = vis[j] = 1;
      adj[i].push_back(j + N); adj[j].push_back(i + N);
      dfs(t + 1);
      adj[i].pop_back(); adj[j].pop_back();
      vis[i] = vis[j] = 0;
    }
  }
}

void solve() {
  cin >> N;

  map<int, vector<pii>> by_y;
  for (int i = 0; i < N; ++i) {
    cin >> X[i] >> Y[i];
    by_y[Y[i]].emplace_back(X[i], i);
  }
  
  memset(nxt, -1, sizeof(nxt));
  for (auto& [y, v] : by_y) {
    sort(v.begin(), v.end());
    int z = v.size();
    for (int i = 1; i < z; ++i) {
      adj[v[i - 1].second + N].push_back(v[i].second);
    }
  }

  dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
