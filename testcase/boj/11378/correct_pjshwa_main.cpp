#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000, INF = 1e9 + 7;

struct Edge {
  int from, to, c, f;
  Edge* rev;
  Edge(int u, int v, int c) : from(u), to(v), c(c), f(0) {}

  int residual() { return c - f; }
  void add(int flow) { f += flow; rev->f -= flow; }
};

vector<Edge*> edges[MAXN + 10];

void add_edge(int u, int v, int c, bool d = 1) {
  Edge* e1 = new Edge(u, v, c);
  Edge* e2 = new Edge(v, u, d ? 0 : c);
  e1->rev = e2;
  e2->rev = e1;
  edges[u].push_back(e1);
  edges[v].push_back(e2);
}

int max_flow(int S, int T) {
  int res = 0;
  while (1) {
    vector<Edge*> from(MAXN + 10, nullptr);
    queue<int> q;
    q.push(S);

    // Find augmenting path
    while (!q.empty() && from[T] == nullptr) {
      int u = q.front(); q.pop();

      for (Edge* e : edges[u]) {
        if (e->residual() > 0 && from[e->to] == nullptr) {
          from[e->to] = e;
          q.push(e->to);
        }
      }
    }

    if (from[T] == nullptr) break;

    int mflo = INF;
    for (int u = T; u != S; u = from[u]->from) mflo = min(mflo, from[u]->residual());
    for (int u = T; u != S; u = from[u]->from) from[u]->add(mflo);
    res += mflo;
  }

  return res;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) {
    int k, x; cin >> k;
    while (k--) {
      cin >> x;
      add_edge(i, N + x, 1);
    }
  }

  int S = 0, T = N + M + 1, U = T + 1;
  for (int i = 1; i <= N; ++i) add_edge(S, i, 1);
  for (int i = N + 1; i <= N + M; ++i) add_edge(i, T, 1);

  add_edge(S, U, K);
  for (int i = 1; i <= N; ++i) add_edge(U, i, K);

  cout << max_flow(S, T) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
