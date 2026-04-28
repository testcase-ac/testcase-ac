#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1005;
int graph[MAX][MAX], nxt[MAX], n;

void dfs(int u) {
  for (int &v = nxt[u]; v < n; v++) {
    while (graph[u][v]) {
      graph[u][v]--;
      graph[v][u]--;
      dfs(v);
    }
  }

  cout << u + 1 << ' ';
}

int main() {
  fast_io();

  cin >> n;
  bool able = true;
  for (int i = 0; i < n; i++) {
    int d = 0;

    for (int j = 0; j < n; j++) {
      cin >> graph[i][j];
      d += graph[i][j];
    }

    if (d & 1) {
      cout << -1;
      return 0;
    }
  }

  dfs(0);
}
