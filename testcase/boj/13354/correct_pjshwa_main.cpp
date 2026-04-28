#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int board[MAX][MAX], parent[MAX * MAX];

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
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) parent[i * m + j] = i * m + j;

  vector<tuple<int, int, int, int>> queries(q);
  for (int i = 0; i < q; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    queries[i] = {x1, y1, x2, y2};

    for (int x = x1; x <= x2; x++) for (int y = y1; y <= y2; y++) board[x - 1][y - 1]++;
  }
  
  vector<int> ans(q);
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j]) continue;

    for (int k = 0; k < 4; k++) {
      int x = i + dx[k], y = j + dy[k];
      if (x < 0 || x >= n || y < 0 || y >= m) continue;
      if (board[x][y] == 0) Union(i * m + j, x * m + y);
    }
  }

  set<int> u;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 0) u.insert(Find(i * m + j));
  }
  int cur = u.size();
  ans[q - 1] = cur;

  for (int i = q - 1; i > 0; i--) {
    auto [x1, y1, x2, y2] = queries[i];
    for (int x = x1 - 1; x <= x2 - 1; x++) for (int y = y1 - 1; y <= y2 - 1; y++) {
      board[x][y]--;
      if (board[x][y]) continue;
      cur++;

      for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (board[nx][ny] == 0 && Find(x * m + y) != Find(nx * m + ny)) {
          cur--;
          Union(x * m + y, nx * m + ny);
        }
      }
    }
    ans[i - 1] = cur;
  }

  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
