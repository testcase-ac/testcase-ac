#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 738;
char board[MAX + 1][MAX + 1];
int parent[MAX * MAX + 1];
bool vis[MAX * MAX + 1];
vector<tuple<int, int, int, char>> graph[MAX * MAX + 1];

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

vector<tii> goals;
unordered_set<int> gset;
int n, m, x, y;

void dfs(int v) {
  if (gset.count(v)) {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      if (board[i][j] == '?') board[i][j] = 'N';
    }
    for (auto [ex, ey, p] : goals) board[ex][ey] = p ? 'P' : 'B';
    for (int i = 0; i < n; i++) cout << board[i] << '\n';
    exit(0);
  }

  vis[v] = 1;
  for (auto [d, i, j, c] : graph[v]) {
    if (vis[d] || board[i][j] != '?') continue;
    board[i][j] = c;
    dfs(d);
    board[i][j] = '?';
  }
  vis[v] = 0;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    parent[i * m + j] = i * m + j;
  }
  cin >> x >> y;
  x--, y--;

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'P' || board[i][j] == 'B') {
      goals.push_back({i, j, board[i][j] == 'P'});
      board[i][j] = '.';
    }
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '.' || board[i][j] == '1') {
      if (j < m - 1 && board[i][j] == board[i][j + 1]) Union(i * m + j, i * m + j + 1);
      if (i < n - 1 && board[i][j] == board[i + 1][j]) Union(i * m + j, (i + 1) * m + j);
    }
  }

  for (auto [ex, ey, p] : goals) gset.insert(Find(ex * m + ey));

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] != '?') continue;
    if (j > 0 && j < m - 1 && board[i][j - 1] == '1' && board[i][j + 1] == '.') {
      graph[Find(i * m + j - 1)].emplace_back(Find(i * m + j + 1), i, j, 'W');
      graph[Find(i * m + j + 1)].emplace_back(Find(i * m + j - 1), i, j, 'W');
    }
    if (j > 0 && j < m - 1 && board[i][j + 1] == '1' && board[i][j - 1] == '.') {
      graph[Find(i * m + j - 1)].emplace_back(Find(i * m + j + 1), i, j, 'E');
      graph[Find(i * m + j + 1)].emplace_back(Find(i * m + j - 1), i, j, 'E');
    }
    if (i > 0 && i < n - 1 && board[i - 1][j] == '1' && board[i + 1][j] == '.') {
      graph[Find((i - 1) * m + j)].emplace_back(Find((i + 1) * m + j), i, j, 'N');
      graph[Find((i + 1) * m + j)].emplace_back(Find((i - 1) * m + j), i, j, 'N');
    }
    if (i > 0 && i < n - 1 && board[i + 1][j] == '1' && board[i - 1][j] == '.') {
      graph[Find((i - 1) * m + j)].emplace_back(Find((i + 1) * m + j), i, j, 'S');
      graph[Find((i + 1) * m + j)].emplace_back(Find((i - 1) * m + j), i, j, 'S');
    }
  }

  dfs(Find(x * m + y));
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
