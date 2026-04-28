#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int board[MAX + 1][MAX + 1];
int dist[MAX + 1][MAX + 1];
int from[MAX + 1][MAX + 1];
pii student[MAX * MAX + 1];

vector<int> graph[MAX * MAX + 1];
int ssize[MAX * MAX + 1];
bool dvis[MAX * MAX + 1];

void dfs(int v) {
  dvis[v] = true;
  ssize[v] = 1;
 
  for (int u : graph[v]) {
    if (!dvis[u]) {
      dfs(u);
      ssize[v] += ssize[u];
    }
  }
}

void solve() {
  int n, m, k, s;
  cin >> n >> m >> k;
  for (int i = 1; i <= k; i++) {
    int x, y;
    cin >> x >> y;
    student[i] = {x, y};
    board[x][y] = i;
  }
  cin >> s;

  memset(dist, -1, sizeof(dist));
  memset(from, -1, sizeof(from));

  queue<tii> q;
  auto [sx, sy] = student[s];
  q.push({sx, sy, 0});
  dist[sx][sy] = 0;

  while (!q.empty()) {
    auto [x, y, d] = q.front();
    q.pop();

    int c = board[x][y];

    for (int i = 0; i < 8; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (board[nx][ny] == 0) continue;

      if (dist[nx][ny] == -1) {
        dist[nx][ny] = d + 1;
        from[nx][ny] = c;
        q.push({nx, ny, d + 1});
      }
      else if (dist[nx][ny] == d + 1) from[nx][ny] = min(from[nx][ny], c);
    }
  }

  for (int i = 1; i <= k; i++) {
    auto [px, py] = student[i];
    if (from[px][py] != -1) {
      graph[from[px][py]].push_back(i);
      graph[i].push_back(from[px][py]);
    }
  }

  dfs(s);
  if (ssize[s] != k) return cout << "-1\n", void();
  for (int i = 1; i <= k; i++) cout << ssize[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
