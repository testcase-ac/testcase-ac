#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

namespace fio {
  const int BSIZE = 1 << 19;
  unsigned char buffer[BSIZE];
  int p = BSIZE;

  inline unsigned char readChar() {
    if (p == BSIZE) {
      fread(buffer, 1, BSIZE, stdin);
      p = 0;
    }
    return buffer[p++];
  }

  template <typename T>
  void readInt(T &ret) {
    unsigned char c = readChar();
    while (c < '-') {
      c = readChar();
    }
    ret = 0; bool neg = c == '-';
    if (neg) c = readChar();
    while (c >= '-') {
      ret = ret * 10 + c - '0';
      c = readChar();
    }
    if (neg) ret = -ret;
  }
}

const int MAXN = 5000, INF = 0x3f3f3f3f;
int cdist[MAXN + 1], U[MAXN + 1], adj[MAXN + 1][MAXN + 1];

void solve() {
  int N, T;
  fio::readInt(N); fio::readInt(T);

  memset(adj, 0x3f, sizeof(adj));
  int x, y, w;
  while (T--) {
    fio::readInt(x); fio::readInt(y); fio::readInt(w);
    adj[x][y] = min(adj[x][y], w);
    adj[y][x] = adj[x][y];
  }

  memset(cdist, 0x3f, sizeof(cdist));
  memset(U, 0x3f, sizeof(U));
  int K; fio::readInt(K);
  while (K--) {
    int x; fio::readInt(x);
    fio::readInt(U[x]);
  }

  // O(N^2) dijkstra
  int D; fio::readInt(D);
  cdist[D] = 0;
  vector<bool> vis(N + 1);
  for (int it = 0; it < N - 1; ++it) {
    int minv = INF, mini;
    for (int v = 1; v <= N; v++) {
      if (!vis[v] && cdist[v] <= minv) minv = cdist[v], mini = v;
    }

    int u = mini;
    vis[u] = true;

    for (int v = 1; v <= N; v++) {
      if (vis[v] || adj[u][v] == INF) continue;
      if (cdist[u] + adj[u][v] < cdist[v]) {
        cdist[v] = cdist[u] + adj[u][v];
      }
    }
  }

  int ans = INF;
  for (int i = 1; i <= N; ++i) ans = min(ans, cdist[i] + U[i]);
  printf("%d\n", ans);
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
