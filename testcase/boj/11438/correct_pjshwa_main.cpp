#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[100001];
int parent[100001][20];
int level[100001];
bool vis[100001];

void dfs(int node, int lv) {
  vis[node] = true;
  level[node] = lv;

  for (int el : graph[node]) {
    if (!vis[el]) {
      parent[el][0] = node;
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

  int n, m, x, y;
  cin >> n;

  for (int i = 0; i < n - 1; i++) {
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  // fill parent array
  dfs(1, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= n; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];

  cin >> m;
  while (m--) {
    cin >> x >> y;

    if (level[x] < level[y]) swap(x, y);
    int diff = level[x] - level[y];

    for (int i = 0; diff; i++) {
      if (diff % 2) x = parent[x][i];
      diff /= 2;
    }

    // level[x] = level[y] from now on.
    if (x != y) {
      for (int i = 19; i >= 0; i--) {
        if (!parent[x][i] || parent[x][i] == parent[y][i]) continue;

        x = parent[x][i];
        y = parent[y][i];
      }

      x = parent[x][0];
    }
    cout << x << '\n';
  }
}
