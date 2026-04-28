#include <bits/stdc++.h>
typedef long long ll;
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<pii> graph[30001];
int parent[30001][20];
int level[30001];
int tdist[30001];
bool vis[30001];
int q[5000];

void dfs(int node, int lv, int cd) {
  vis[node] = true;
  level[node] = lv;
  tdist[node] = cd;

  for (auto[nv, nd] : graph[node]) {
    if (!vis[nv]) {
      parent[nv][0] = node;
      dfs(nv, lv + 1, cd + nd);
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
    graph[x].push_back({y, 1});
    graph[y].push_back({x, 1});
  }

  // fill parent array
  dfs(1, 0, 0);
  for (int j = 0; j < 20; j++)
    for (int i = 2; i <= n; i++)
      if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];

  cin >> m;
  for (int i = 0; i < m; i++) cin >> q[i];

  int dist;
  long long dsum = 0;
  for (int i = 0; i < m - 1; i++) {
    x = q[i]; y = q[i + 1];
    dist = tdist[x] + tdist[y];

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
    dsum += (dist - 2 * tdist[x]);
  }

  cout << dsum << '\n';
}
