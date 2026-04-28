#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tlll = tuple<ll, ll, ll, ll>;

const int MAX = 50;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
const ll INF = 1e18;
pll cdist[MAX][MAX];
int n, m;

bool adj(int i, int j) {
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= n || y < 0 || y >= m) continue;
    if (board[x][y] == 'g') return true;
  }
  return false;
}

void dijk(int si, int sj) {
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cdist[i][j] = {INF, INF};
  cdist[si][sj] = {0, 0};

  priority_queue<tlll, vector<tlll>, greater<tlll>> pq;
  pq.push({0, 0, si, sj});

  while (!pq.empty()) {
    auto [wx, wy, ui, uj] = pq.top();
    pq.pop();

    auto [px, py] = cdist[ui][uj];
    if (wx > px || (wx == px && wy > py)) continue;

    for (int k = 0; k < 4; k++) {
      int vi = ui + dx[k], vj = uj + dy[k];
      if (vi < 0 || vi >= n || vj < 0 || vj >= m) continue;

      ll nx = wx, ny = wy;
      if (board[vi][vj] == 'g') nx++;
      else if (board[vi][vj] == '.' && adj(vi, vj)) ny++;

      auto [vpx, vpy] = cdist[vi][vj];
      if (nx < vpx || (nx == vpx && ny < vpy)) {
        cdist[vi][vj] = {nx, ny};
        pq.push({nx, ny, vi, vj});
      }
    }
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int si, sj, ei, ej;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'S') si = i, sj = j;
    if (board[i][j] == 'F') ei = i, ej = j;
  }

  dijk(si, sj);
  cout << cdist[ei][ej].first << ' ' << cdist[ei][ej].second << '\n';
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
