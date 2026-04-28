#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3;
int n, m;
char board[MAX + 1][MAX + 1];
int vis[MAX + 1][MAX + 1];
int parent[MAX * MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void dfs(int i, int j, int cc) {
  vis[i][j] = cc;

  if (board[i][j] == 'U') {
    if (vis[i - 1][j]) Union(vis[i - 1][j], cc);
    else dfs(i - 1, j, cc);
  }
  if (board[i][j] == 'D') {
    if (vis[i + 1][j]) Union(vis[i + 1][j], cc);
    else dfs(i + 1, j, cc);
  }
  if (board[i][j] == 'L') {
    if (vis[i][j - 1]) Union(vis[i][j - 1], cc);
    else dfs(i, j - 1, cc);
  }
  if (board[i][j] == 'R') {
    if (vis[i][j + 1]) Union(vis[i][j + 1], cc);
    else dfs(i, j + 1, cc);
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i <= MAX * MAX; i++) parent[i] = i;

  int cc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (!vis[i][j]) dfs(i, j, ++cc);
  }

  set<int> safe_zones;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) safe_zones.insert(Find(vis[i][j]));
  cout << safe_zones.size() << '\n';
}
