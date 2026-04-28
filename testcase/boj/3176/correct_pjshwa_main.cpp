#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<pair<int, int>> graph[100001];
int parent[100001][21];
int minv[100001][21];
int maxv[100001][21];
int level[100001];
bool vis[100001];

void dfs(int node, int lv) {
  vis[node] = true;
  level[node] = lv;

  for (auto [el, nd] : graph[node]) {
    if (!vis[el]) {
      parent[el][0] = node;
      minv[el][0] = maxv[el][0] = nd;
      dfs(el, lv + 1);
    }
  }
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  fast_io();

  int n, m, x, y, d;
  cin >> n;

  for (int i = 0; i < n - 1; i++) {
    cin >> x >> y >> d;
    graph[x].push_back({y, d});
    graph[y].push_back({x, d});
  }

  // fill parent array
  dfs(1, 0);
  for (int j = 1; j <= 20; j++) for (int i = 1; i <= n; i++) {
    parent[i][j] = parent[parent[i][j - 1]][j - 1];
    minv[i][j] = min(minv[i][j - 1], minv[parent[i][j - 1]][j - 1]);
    maxv[i][j] = max(maxv[i][j - 1], maxv[parent[i][j - 1]][j - 1]);
  }

  cin >> m;
  while (m--) {
    cin >> x >> y;

    int mn = 1e9, mx = -1e9;

    if (level[x] < level[y]) swap(x, y);
    int diff = level[x] - level[y];

    for (int i = 0; diff; i++) {
      if (diff % 2) {
        mn = min(mn, minv[x][i]);
        mx = max(mx, maxv[x][i]);
        x = parent[x][i];
      }
      diff /= 2;
    }

    // level[x] = level[y] from now on.
    if (x != y) {
      for (int i = 20; i >= 0; i--) {
        if (parent[x][i] == parent[y][i]) continue;

        mn = min(mn, minv[x][i]);
        mn = min(mn, minv[y][i]);

        mx = max(mx, maxv[x][i]);
        mx = max(mx, maxv[y][i]);

        x = parent[x][i];
        y = parent[y][i];
      }

      mn = min(mn, minv[x][0]);
      mn = min(mn, minv[y][0]);

      mx = max(mx, maxv[x][0]);
      mx = max(mx, maxv[y][0]);
    }

    cout << mn << ' ' << mx << '\n';
  }
}
