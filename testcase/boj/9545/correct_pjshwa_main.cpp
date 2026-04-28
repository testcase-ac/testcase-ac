#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 26;
bool mark[MAX][MAX];
vector<int> graph[MAX];
bool vis[MAX];
int mdepth;

void dfs(int v, int d) {
  vis[v] = true;
  if (d % 2 == 0) mdepth = max(mdepth, d);

  for (int u : graph[v]) {
    if (!vis[u]) {
      dfs(u, d + 1);
    }
  }
}

vector<int> current;
int board[20][20];
bool printed;

void print_board() {
  for (int i = 0; i < 20; i++) {
    if (board[i][0] == -1) break;
    for (int j = 0; j < 20; j++) {
      if (board[i][j] == -1) break;
      cout << board[i][j] << " ";
    }
    cout << '\n';
  }
}

void fill_board() {
  int side = mdepth / 2 + 1;

}

void dfs2(int v) {
  if (printed) return;

  if (current.size() == mdepth + 1) {
    fill_board();
    print_board();
    printed = true;
    return;
  }

  for (int u : graph[v]) {
    if (!vis[u]) {
      vis[u] = true;
      current.push_back(u);
      dfs2(u);
      current.pop_back();
      vis[u] = false;
    }
  }
}

void solve() {
  int m;
  cin >> m;

  memset(mark, 0, sizeof(mark));
  memset(vis, 0, sizeof(vis));
  memset(board, -1, sizeof(board));
  printed = false;
  for (int i = 0; i < MAX; i++) graph[i].clear();
  mdepth = 0;

  while (m--) {
    string s;
    cin >> s;
    mark[s[0] - 'a'][s[1] - 'a'] = true;
  }

  for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) {
    if (!mark[i][j]) graph[i].push_back(j);
  }

  for (int i = 0; i < MAX; i++) if (!vis[i]) dfs(i, 0);
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < MAX; i++) if (!vis[i]) {
    vis[i] = true;
    current.push_back(i);
    dfs2(i);
    current.pop_back();
    vis[i] = false;
  }
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
