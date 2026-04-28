#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXV = 6e5, INF = 0x3f3f3f3f;
vector<int> X[MAXN + 1], adj[MAXV + 1];
int B[MAXV + 1], cdist[MAXV + 1];
unordered_map<ll, int> node_id_map;

ll node_id_key(int i, int x) {
  return (ll)x * MAXN + (i - 1);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<tuple<int, int, int, int>> edges;
  for (int j = 0; j < M; ++j) {
    int a, b, x, y; cin >> a >> b >> x >> y;
    edges.emplace_back(a, b, x, y);
    X[a].push_back(x); X[b].push_back(y);
  }

  int it = 0;
  for (int i = 1; i <= N; ++i) {
    sort(X[i].begin(), X[i].end());
    X[i].erase(unique(X[i].begin(), X[i].end()), X[i].end());
    for (int x : X[i]) node_id_map[node_id_key(i, x)] = ++it;
  }

  for (auto& [a, b, x, y] : edges) {
    int u = node_id_map[node_id_key(a, x)], v = node_id_map[node_id_key(b, y)];
    B[u] = x; B[v] = y;
    adj[v].push_back(u);
  }
  for (int i = 1; i <= N; ++i) {
    int Z = X[i].size();
    for (int j = 1; j < Z; ++j) {
      int u = node_id_map[node_id_key(i, X[i][j - 1])];
      int v = node_id_map[node_id_key(i, X[i][j])];
      adj[v].push_back(u);
    }
  }

  using T = pair<int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  fill(cdist + 1, cdist + it + 1, INF);
  for (int e : X[N]) {
    int v = node_id_map[node_id_key(N, e)];
    cdist[v] = B[v];
    pq.emplace(cdist[v], v);
  }

  while (!pq.empty()) {
    auto [d, v] = pq.top(); pq.pop();
    if (cdist[v] < d) continue;

    for (int u : adj[v]) {
      if (cdist[u] > d) {
        cdist[u] = d;
        pq.emplace(cdist[u], u);
      }
    }
  }

  vector<pii> R;
  for (int e : X[1]) {
    int v = node_id_map[node_id_key(1, e)];
    if (cdist[v] != INF) R.emplace_back(cdist[v], e);
  }
  sort(R.begin(), R.end());

  int Q; cin >> Q;
  while (Q--) {
    int x; cin >> x;
    auto it = upper_bound(R.begin(), R.end(), pii(x, INF));
    if (it == R.begin()) cout << "-1\n";
    else cout << (--it)->second << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
