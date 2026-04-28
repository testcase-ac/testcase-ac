#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
char board[MAX + 1][MAX + 1];
vector<tii> graph[MAX + 1][MAX + 1];
int cdist[MAX + 1][MAX + 1];
int n, m;

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    for (int k = 0; k < 8; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      graph[i][j].push_back({ni, nj, k == board[i][j] - '0' ? 0 : 1});
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int si, sj, ei, ej;
    cin >> si >> sj >> ei >> ej;
    si--, sj--, ei--, ej--;

    // 0-1 bfs
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cdist[i][j] = INF;
    deque<tii> qq;
    cdist[si][sj] = 0;
    qq.push_back({si, sj, 0});

    while (!qq.empty()) {
      auto [i, j, d] = qq.front();
      qq.pop_front();

      if (i == ei && j == ej) {
        cout << d << '\n';
        break;
      }

      for (auto &[ni, nj, nd] : graph[i][j]) {
        if (cdist[ni][nj] > d + nd) {
          cdist[ni][nj] = d + nd;
          if (nd) qq.push_back({ni, nj, d + nd});
          else qq.push_front({ni, nj, d + nd});
        }
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
