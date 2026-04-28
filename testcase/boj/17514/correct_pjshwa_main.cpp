#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5, MAXT = 1e6, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1], radj[MAXN + 1];
int padj[MAXN + 1], cadj[MAXN + 1];
int N;

bool is_reachable(int S, int T) {
  vector<int> dist(N + 1, INF);
  queue<int> q;
  q.push(S); dist[S] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (auto [v, _] : adj[u]) {
      if (dist[v] == INF) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
  return dist[T] != INF;
}

void solve() {
  int M, S, T; cin >> N >> M >> S >> T;

  vector<tuple<int, int, int>> edges;
  while (M--) {
    int u, v, c; cin >> u >> v >> c;
    adj[u].emplace_back(v, c);
    radj[v].emplace_back(u, c);
    edges.emplace_back(u, v, c);
  }
  if (!is_reachable(S, T)) return cout << "IMPOSSIBLE\n", void();

  vector<bool> R(N + 1, false);
  queue<int> q; q.push(T); R[T] = true;
  while (!q.empty()) {int u = q.front(); q.pop(); for (auto [v, _] : radj[u]) if (!R[v]) q.push(v), R[v] = true;}

  memset(padj, -1, sizeof(padj));
  memset(cadj, 0x3f, sizeof(cadj));
  for (auto& [u, v, c] : edges) {
    if (!(R[u] && R[v])) continue;
    if (c < cadj[u]) padj[u] = v, cadj[u] = c;
  }

  vector<int> traj; int e = S;
  while (traj.size() <= MAXT) {
    traj.push_back(cadj[e]);
    e = padj[e];
    if (e == T) break;
  }

  if (traj.size() > MAXT) cout << "TOO LONG";
  else for (int u : traj) cout << u << " ";
  cout << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
