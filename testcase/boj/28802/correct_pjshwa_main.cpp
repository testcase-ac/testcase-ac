#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void quit() {
  cout << "No\n";
  exit(0);
}

void m_assert(bool b) {
  if (!b) quit();
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
vector<int> adj[MAXN + 1];
int deg[MAXN + 1], cdist[MAXN + 1], from[MAXN + 1], vis[MAXN + 1], V, E;

void bfs(int s) {
  fill(cdist + 1, cdist + V + 1, INF);
  queue<int> q;
  q.push(s); cdist[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (cdist[v] > cdist[u] + 1) {
        cdist[v] = cdist[u] + 1;
        from[v] = u;
        q.push(v);
      }
    }
  }
}

void solve() {
  int N, M; cin >> N >> M;
  V = N * M, E = N * (M - 1) + M * (N - 1);
  for (int j = 0; j < E; ++j) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); ++deg[v];
    adj[v].push_back(u); ++deg[u];
  }

  vector<int> O;
  for (int i = 1; i <= V; ++i) if (deg[i] == 2) O.push_back(i);
  m_assert(O.size() == 4);

  int S = O[0], T; bfs(S);
  for (T = 1; T < 4; ++T) if (cdist[O[T]] == M - 1) break;
  m_assert(T < 4);
  T = O[T];

  vector<int> L{T};
  while (from[L.back()] != S) L.push_back(from[L.back()]);
  L.push_back(S);
  for (int j = 0; j < M; ++j) {
    int expected = (j == 0 || j == M - 1) ? 2 : 3;
    m_assert(deg[L[j]] == expected);
    vis[L[j]] = 1;
  }

  for (int i = 1; i < N; ++i) {
    vector<int> nL;
    for (int j = 0; j < M; ++j) {
      int nv = -1;
      for (int v : adj[L[j]]) {
        if (vis[v]) continue;
        if (nv == -1) nv = v;
        else m_assert(false);
      }
      m_assert(nv != -1);
      nL.push_back(nv);
    }
    for (int j = 0; j < M; ++j) {
      int expected = (j == 0 || j == M - 1) ? 3 : 4;
      if (i == N - 1) --expected;
      m_assert(deg[nL[j]] == expected);
      vis[nL[j]] = 1;
    }
    L = nL;
  }

  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
