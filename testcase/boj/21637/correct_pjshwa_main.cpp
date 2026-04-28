#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1], rboard[MAX + 1][MAX + 1];
int vis[MAX][MAX], fld[MAX][MAX], dsb[MAX * MAX + 1];
int indegree[MAX * MAX + 1], qvis[MAX * MAX + 1];
pii inv[MAX * MAX + 1];
int n, m;
vector<int> graph[MAX * MAX + 1];
int unfld[MAX + 1][MAX + 1], unfolded;

bool is_upper(char c) {
  return 'A' <= c && c <= 'Z';
}

void check(int cc) {
  auto [i, j] = inv[cc];

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

    if (board[i][j] == board[ni][nj]) {
      unfld[i][j] = unfld[ni][nj] = cc;
      break;
    }
  }

}

void unfold(int cc) {
  unfolded++;
  auto [i, j] = inv[cc];

  int ni, nj, f = 0;
  for (int k = 0; k < 4; k++) {
    ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

    if (board[i][j] == board[ni][nj]) {
      f = 1;
      break;
    }
  }
  if (!f) return;

  if (is_upper(board[i][j])) {
    if (abs(i - ni) == 1) {
      unfld[i][j + 1] = unfld[ni][nj + 1] = cc;
    }
    else {
      unfld[i + 1][j] = unfld[ni + 1][nj] = cc;
    }
  }
  else {
    if (abs(i - ni) == 1) {
      unfld[i][j - 1] = unfld[ni][nj - 1] = cc;
    }
    else {
      unfld[i - 1][j] = unfld[ni - 1][nj] = cc;
    }
  }
}

void mark(int i, int j, int cc) {
  vis[i][j] = cc;
  inv[cc] = {i, j};

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
    if (vis[ni][nj]) continue;

    if (board[ni][nj] == board[i][j]) {
      mark(ni, nj, cc);

      if (is_upper(board[i][j])) {
        if (abs(i - ni) == 1) {
          if (j != m - 1 && board[i][j + 1] == '.' && board[ni][nj + 1] == '.') {
            if (fld[i][j + 1]) {
              int u = fld[i][j + 1], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[i][j + 1] = cc;

            if (fld[ni][nj + 1]) {
              int u = fld[ni][nj + 1], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[ni][nj + 1] = cc;
          }
          else dsb[cc] = 1;
        }
        else {
          if (i != n - 1 && board[i + 1][j] == '.' && board[ni + 1][nj] == '.') {
            if (fld[i + 1][j]) {
              int u = fld[i + 1][j], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[i + 1][j] = cc;

            if (fld[ni + 1][nj]) {
              int u = fld[ni + 1][nj], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[ni + 1][nj] = cc;
          }
          else dsb[cc] = 1;
        }
      }
      else {
        if (abs(i - ni) == 1) {
          if (j != 0 && board[i][j - 1] == '.' && board[ni][nj - 1] == '.') {
            if (fld[i][j - 1]) {
              int u = fld[i][j - 1], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[i][j - 1] = cc;

            if (fld[ni][nj - 1]) {
              int u = fld[ni][nj - 1], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[ni][nj - 1] = cc;
          }
          else dsb[cc] = 1;
        }
        else {
          if (i != 0 && board[i - 1][j] == '.' && board[ni - 1][nj] == '.') {
            if (fld[i - 1][j]) {
              int u = fld[i - 1][j], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[i - 1][j] = cc;

            if (fld[ni - 1][nj]) {
              int u = fld[ni - 1][nj], v = cc;
              graph[u].push_back(v);
              graph[v].push_back(u);
            }
            else fld[ni - 1][nj] = cc;
          }
          else dsb[cc] = 1;
        }

      }
    }
  }
}

set<int> adj_nums;
void nodup_number_dfs(int i, int j) {
  vis[i][j] = 1;
  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
    if (unfld[ni][nj] == 0 || unfld[i][j] == unfld[ni][nj]) continue;

    if ('1' <= board[ni][nj] && board[ni][nj] <= '9') {
      adj_nums.insert(board[ni][nj] - '0');
    }
  }

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

    if (unfld[ni][nj] == unfld[i][j] && !vis[ni][nj]) nodup_number_dfs(ni, nj);
  }
}

void mark_number_dfs(int i, int j, int num) {
  char d = num + '0';
  board[i][j] = d;

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

    if (unfld[i][j] == unfld[ni][nj] && board[ni][nj] != d) mark_number_dfs(ni, nj, num);
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int cc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '.') continue;
    if (vis[i][j]) continue;
    mark(i, j, ++cc);
  }

  for (int i = 1; i <= cc; i++) {
    for (int j : graph[i]) {
      indegree[j]++;
    }
  }

  queue<pii> q;
  for (int i = 1; i <= cc; i++) {
    if (indegree[i] != 1) continue;
    if (qvis[i]) continue;

    q.push({i, 0});
    qvis[i] = 1;

    while (!q.empty()) {
      auto [v, p] = q.front(); q.pop();

      check(v);
      if (p % 2 == 0) unfold(v);

      for (int u : graph[v]) {
        if (qvis[u]) continue;
        q.push({u, p + 1});
        qvis[u] = 1;
      }
    }
  }

  // Get rid of cycles && unused
  for (int i = 1; i <= cc; i++) {
    if (qvis[i]) continue;

    q.push({i, 0});
    qvis[i] = 1;

    while (!q.empty()) {
      auto [v, p] = q.front(); q.pop();

      check(v);
      if (!dsb[v] && p % 2 == 0) unfold(v);

      for (int u : graph[v]) {
        if (qvis[u]) continue;
        q.push({u, p + 1});
        qvis[u] = 1;
      }
    }
  }

  cout << unfolded << '\n';

  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (unfld[i][j] == 0 || vis[i][j]) continue;

      adj_nums.clear();
      nodup_number_dfs(i, j);

      int mex = 1;
      while (adj_nums.count(mex)) mex++;

      mark_number_dfs(i, j, mex);
    }
  }

  for (int i = 0; i < n; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
