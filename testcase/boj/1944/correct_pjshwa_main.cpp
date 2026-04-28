#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX];
int parent[MAX * MAX];

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

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n * n; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == '0' || board[i][j] == '1') continue;

    memset(vis, 0, sizeof(vis));
    queue<tii> q;
    q.push({i, j, 0});
    vis[i][j] = 1;

    while (!q.empty()) {
      int x, y, d;
      tie(x, y, d) = q.front();
      q.pop();

      if (board[x][y] != '0') ta.push_back({d, i * n + j, x * n + y});

      for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (board[nx][ny] == '1') continue;
        if (vis[nx][ny]) continue;

        vis[nx][ny] = 1;
        q.push({nx, ny, d + 1});
      }
    }
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  int uc = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    uc++;
    Union(x, y);
  }

  if (uc == m) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
