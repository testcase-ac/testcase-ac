#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, INF = 0x3f3f3f3f;
int g[MAX + 1][MAX + 1], cdist[MAX + 1];
vector<int> graph[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    cin >> g[i][j];
    if (g[i][j] == 1) graph[i].push_back(j);
  }

  for (int w = 1; w < N; w = w + 1) {
    for (int u = 1; u <= N; u = u + 1) {
      g[u][N] = min(g[u][N], g[u][w] + g[w][N]);
      g[N][u] = min(g[N][u], g[N][w] + g[w][u]);
    }
  }

  for (int u = 1; u <= N; u = u + 1) {
    for (int v = 1; v <= N; v = v + 1) {
      g[u][v] = min(g[u][v], g[u][N] + g[N][v]);
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) cout << g[i][j] << " ";
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
