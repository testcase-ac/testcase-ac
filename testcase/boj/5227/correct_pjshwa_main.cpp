#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN];
int G[MAXN], indegree[MAXN];

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

int dfs(int v) {
  if (G[v] != -1) return G[v];
  if (adj[v].empty()) return G[v] = 0;

  vector<int> Gs;
  for (int u : adj[v]) Gs.push_back(dfs(u));
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return G[v] = mex;
}

int N, M;
void solve() {
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    G[i] = -1;
    indegree[i] = 0;
  }
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    ++indegree[v];
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    while (x--) ans ^= dfs(i);
  }

  if (ans == 0) cout << "Second\n";
  else cout << "First\n";
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
