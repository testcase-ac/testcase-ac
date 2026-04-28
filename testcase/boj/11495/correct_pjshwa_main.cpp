#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;

struct Edge {
  int from, to, c, f;
  Edge* rev;
  Edge(int u, int v, int c) : from(u), to(v), c(c), f(0) {}

  int residual() { return c - f; }
  void add(int flow) { f += flow; rev->f -= flow; }
};

vector<Edge*> edges[MAX * MAX + 10];

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
    vector<Edge*> from(MAX * MAX + 10, nullptr);
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

int board[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n * m + 2; i++) edges[i].clear();

  int S = n * m, T = S + 1;

  ll sum = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> board[i][j];
    sum += board[i][j];

    int u = i * m + j;
    if ((i + j) & 1) add_edge(u, T, board[i][j]);
    else add_edge(S, u, board[i][j]);
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if ((i + j) & 1) continue;

    int u = i * m + j;
    if (i > 0) add_edge(u, u - m, INF);
    if (j > 0) add_edge(u, u - 1, INF);
    if (i < n - 1) add_edge(u, u + m, INF);
    if (j < m - 1) add_edge(u, u + 1, INF);
  }

  cout << sum - max_flow(S, T) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
